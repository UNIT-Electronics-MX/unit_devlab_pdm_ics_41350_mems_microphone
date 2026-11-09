## **5 Board Operation**

This example uses the
[DevLab_AudioInput library](https://github.com/UNIT-Electronics-MX/unit_devlab_audioinput_library)
to convert PDM input to signed 16-bit mono PCM. The example is shown on an
ESP32-S3; other hosts with a PDM receiver can use the same connections,
adjusting the pins and sketch settings to the board.

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

#if defined(ARDUINO_ARCH_RP2040)
#define PDM_CLK_PIN  10
#define PDM_DATA_PIN 11
#else
#define PDM_CLK_PIN  GPIO_NUM_2
#define PDM_DATA_PIN GPIO_NUM_3
#endif

DevLab_AudioInput pdm;
int16_t samples[512];

void setup() {
  Serial.begin(115200);
  delay(1000);

  if (!pdm.beginPDM(PDM_CLK_PIN, PDM_DATA_PIN)) {
    Serial.println("PDM initialization failed.");
    while (true) delay(1000);
  }
}

void loop() {
  size_t n = pdm.read(samples, 512);
  if (n == 0) return;

  // Peak level of the block
  int32_t peak = 0;
  for (size_t i = 0; i < n; i++) {
    int32_t v = abs(static_cast<int32_t>(samples[i]));
    if (v > peak) peak = v;
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

The library's PDM sketches use CLK on GPIO2 and DATA on GPIO3 on an
ESP32-S3, the same pins as the wiring table in Section 5.1. To use them with
the UE0148 default channel, pass `I2S_PDM_SLOT_RIGHT` as the fourth argument
of `beginPDM()`.

**Serial streaming protocol.** `SerialStream` and `ComputerAudio` send raw
audio over the serial port instead of text:

| Item | `SerialStream` | `ComputerAudio` |
|---|---|---|
| Sample rate | 48 kHz | 16 kHz |
| Baud rate | 2000000 | 921600 |
| Format | PCM16, mono, little-endian, no delimiters between samples | PCM16, mono, little-endian, no delimiters between samples |
| Start | Sends a `RAW` line, then streams | Waits for `R`, answers with a `RAW` line, then streams |
| Commands | `R` starts or resynchronizes, `S` stops, `G<percent>` sets gain (for example `G200` for 200 %) | `R` starts, `S` stops |
| Gain | 100 % until changed with `G` | Fixed at 800 % in the sketch |

Close the Arduino Serial Monitor before connecting another application to
the serial port. The receiver uses the sample rate and baud rate in the table.
`SerialSamples` prints every PCM16 sample as text at 8 kHz for inspecting the
waveform; at 115200 baud it can lose samples in real time, so use
`SerialStream` or `ComputerAudio` to capture audio.

**Playing audio on a computer.** `ComputerAudio` has a companion Python
script, `pc_audio.py`, in the same folder. It plays the stream through the computer's
audio output:

1. Install the dependencies with `pip install pyserial sounddevice`.
2. Upload the `ComputerAudio` sketch to the host board.
3. Close the Arduino Serial Monitor.
4. From the folder that contains `pc_audio.py`, run the script with Python,
   passing the serial port of your host board as the argument.

The script sends `R` until it receives the `RAW` header and then plays the
stream until you press Ctrl+C. The `SAMPLE_RATE` and `BAUD_RATE` values in the
sketch and in `pc_audio.py` must match. The optional `--device` argument selects
another audio output device; the `sounddevice` module can list the devices
available on your computer.

If initialization fails, the host configuration checks PDM-to-PCM support,
the Arduino core version, and GPIO availability. If captured samples
remain near zero, the signal check covers power, clock, `DATA`, and the
receiver slot relative to `CH`. If samples clip or show noise, the check
covers the supply, clock waveform, acoustic port, and host gain.
