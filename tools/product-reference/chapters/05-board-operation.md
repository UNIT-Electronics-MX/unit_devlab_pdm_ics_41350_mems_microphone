## **5 Board Operation**

This example uses the
[DevLab_AudioInput library](https://github.com/UNIT-Electronics-MX/unit_devlab_audioinput_library)
to convert PDM input to signed 16-bit mono PCM on an ESP32-S3. The library
supports ESP32-S3 hardware capture and compiles for RP2040/RP2350. The
ESP32-C6 lacks the PDM-to-PCM peripheral used by the library's `read()` path.

### **5.1 Wiring and First Power-Up**

The connection uses a clear acoustic port, a common ground, and a supply
that follows the module power circuit. The board revision and solder
options determine the effective channel selection. The sensor VDD range
describes the microphone pin rather than the module `VIN` input.

| UE0148 signal | Example ESP32-S3 pin | Direction |
|---|---|---|
| `CLK` | GPIO2 | Host PDM clock output |
| `DATA` | GPIO3 | Host PDM data input |
| `CH` | Board default low | Right channel |
| `GND` | GND | Common ground |
| `VIN` or `VSYS` | Supply matching the board power circuit | Board power |

The UE0148 circuit pulls `CH` low and selects the right PDM channel by
default. If the assembled board selects left, the sketch uses
`I2S_PDM_SLOT_LEFT`. The GPIO numbers identify host pins; the
four-position connector carries `CLK`, `DATA`, `VSYS`, and `GND`.

```{=latex}
\clearpage
```

```{=openxml}
<w:p><w:r><w:br w:type="page"/></w:r></w:p>
```

### **5.2 Arduino Library Example**

The example requires the library in the Arduino sketchbook and an ESP32-S3
with Arduino-ESP32 3.x. Arduino Library Manager lists `DevLab_AudioInput`:

![DevLab_AudioInput entry in Arduino Library Manager.](hardware/resources/external/audioinput_library.png){width=2.5in}

```{=latex}
\clearpage
```

```{=openxml}
<w:p><w:r><w:br w:type="page"/></w:r></w:p>
```

The complete
[AudioInputBasicRead sketch](https://github.com/UNIT-Electronics-MX/unit_devlab_pdm_ics_41350_mems_microphone/blob/main/software/examples/pdm/cpp_examples/AudioInputBasicRead/AudioInputBasicRead.ino)
reports the absolute peak of each captured PCM16 block at 115200 baud:

```cpp
#include <DevLab_AudioInput.h>
DevLab_AudioInput microphone;
int16_t samples[256];

void setup() {
  Serial.begin(115200);
  if (!microphone.beginPDM(GPIO_NUM_2, GPIO_NUM_3, 48000,
                           I2S_PDM_SLOT_RIGHT)) {
    Serial.println("PDM initialization failed");
    while (true) delay(1000);
  }
  delay(25);
}

void loop() {
  size_t count = microphone.read(samples, 256);
  if (count == 0) return;
  int32_t peak = 0;
  for (size_t i = 0; i < count; ++i) {
    int32_t value = samples[i];
    if (value < 0) value = -value;
    if (value > peak) peak = value;
  }
  Serial.println(peak);
}
```

The Serial Monitor displays the peak at 115200 baud. The peak changes with
sound level and represents digital PCM amplitude. A logic analyzer shows
the actual PDM clock frequency and its corresponding sensor mode.

### **5.3 Other Capture Examples and Checks**

The library's `examples/PDM` folder also provides `SerialPlotter`,
`SerialStream`, `SerialSamples`, and `ComputerAudio`. Its stock
examples use the library's default left slot; the UE0148 default uses
`I2S_PDM_SLOT_RIGHT`. The existing
[LegacySerialStream sketch](https://github.com/UNIT-Electronics-MX/unit_devlab_pdm_ics_41350_mems_microphone/blob/main/software/examples/pdm/cpp_examples/LegacySerialStream/LegacySerialStream.ino)
uses the ESP-IDF driver directly and selects the board's drawn right slot.
It is retained as an experimental legacy sketch.

If initialization fails, the host configuration checks PDM-to-PCM support,
the Arduino core version, and GPIO availability. If captured samples
remain near zero, the signal check covers power, clock, `DATA`, and the
receiver slot relative to `CH`. If samples clip or show noise, the check
covers the supply, clock waveform, acoustic port, and host gain.
