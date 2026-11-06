## **3 Functional Overview**

### **3.1 Block Diagram** {.section-page}

The block diagram shows the main functional blocks of the UE0148 module and
the signals available.

![UE0148 PDM ICS-41350 microphone module block diagram.](hardware/resources/external/pdm_ics_41350_mems_microphone.png){width=6.3in}

The host drives `CLK`; the microphone drives `DATA` toward the host. `VIN`
feeds a 3.3 V regulator whose output reaches the microphone through the
`VSYS` rail. Section 2 specifies the sensor supply range.

### **3.2 Microphone and PDM Signal Path**

Sound enters the ICS-41350 (MK1) through its bottom acoustic port. A MEMS
sensing element and impedance-converter amplifier feed a fourth-order
sigma-delta modulator, and the `DATA` pin carries its 1-bit PDM output. The
host supplies `CLK`, then decimates and filters the PDM bitstream to obtain
audio samples. The
[ICS-41350 datasheet](https://unit-electronics-mx.github.io/unit_devlab_pdm_ics_41350_mems_microphone/hardware/resources/external/ds-000047-ics-41350-datasheet.pdf)
describes this path in its functional block diagram and “Theory of Operation. ”

The microphone has no register map and no configuration bus. Only three
signals reach it from the connectors: `CLK` and `DATA` for the audio stream,
and `CH` for channel selection. The `VSYS` rail powers it.

### **3.3 Clock Modes and Control Signals**

The sensor has no mode register. Its clock frequency selects the mode:

| Sensor mode | `CLK` frequency | Typical sensor current | Typical sensitivity |
|---|---:|---:|---:|
| Sleep | Below 200 kHz | 12 µA | No data output |
| Low power | 400–800 kHz | 185 µA | −26 dB FS |
| Standard | 1.0–3.3 MHz | 430 µA | −26 dB FS |
| High performance | 4.1–4.8 MHz | 650 µA | −32 dB FS |

The table lists **sensor** characteristics from DS-000047. Clock ranges
between listed modes lie outside the specified operating modes. Below
200 kHz, `DATA` becomes high impedance. After a valid clock starts, the
microphone takes up to 20 ms to wake and settle. High-performance mode
supports ultrasonic capture up to 40 kHz only when the host decimation
filter and acoustic path also preserve that band.

**Channel selection.** The ICS-41350 `SELECT` pin low selects the right
channel (DATA1); high at sensor VDD selects the left channel (DATA2).
Right-channel bits are clocked on the rising edge and left-channel bits on
the falling edge. The microphone releases `DATA` outside its selected
half-cycle, so one left and one right microphone can share a data line and
a clock. The datasheet specifies a shared PDM data line without a pull-up
or pull-down.

The UE0148 schematic routes board `CH` to the sensor `SELECT` net. R5 (0 Ω)
ties that net to a node that R3 (10 kΩ) pulls to ground, and a solder
option can connect the same node to `VSYS`. The circuit therefore selects
the **right** channel by default, and the assembled solder option
determines the effective selection. The host PDM receiver selects the same
channel as the microphone. The four-position connector carries `CLK` and
`DATA`, but not `CH`; channel selection through that connector uses the
board option.

### **3.4 Power Section**

The schematic identifies U3 as an AP2112K-3.3 fixed regulator supplied from
`VIN`. Its output passes through the Schottky diode D2 (NSR0320MW2T1G) to
`VSYS`, and the microphone VDD pin is on `VSYS`. The schematic annotates
`VIN` as input only and `VSYS` as bidirectional (I/O). Both rails are
available on the edge connections; J2 exposes `VSYS`.

The regulator uses 1 µF capacitors C8 (input) and C9 (`VSYS`). The
microphone VDD pin has a 100 nF capacitor (C6) and a 200 pF capacitor (C1)
to ground. An orange power LED (D1) connects from `VSYS` through R1 (4.7 kΩ)
and a solder option (`LED ON ENABLE`) to ground.

The ICS-41350 VDD operating range of 1.65–3.63 V applies at the sensor pin;
the module supply path determines the voltage at that pin. The module `VIN`
input range, current consumption, and backfeed behavior through `VSYS`
require board validation and do not follow from the regulator or diode
component ratings.

### **3.5 Communication Interface**

The ICS-41350 provides a single digital interface, PDM, which connects
directly to microcontrollers and audio processors that include a PDM
receiver.

**PDM Interface**

- 1-bit pulse-density-modulated output, host-supplied clock
- Sensor clock range from 400 kHz to 4.8 MHz in the specified operating modes
- Two selectable channels (right or left) through the `SELECT` pin
- Shared `DATA` line for a left/right microphone pair

The host drives `CLK` and receives `DATA`. The sensor does not process audio
into PCM; the host receiver converts the PDM stream to PCM, using dedicated
hardware (for example, the PDM-to-PCM converter of the ESP32-S3) or software
filtering. The audio sample rate follows from the PDM clock frequency and the
host decimation ratio, and the PDM clock frequency also selects the sensor
mode (Section 3.3).

### **3.6 Library Features**

The [DevLab_AudioInput](https://github.com/UNIT-Electronics-MX/unit_devlab_audioinput_library)
library for Arduino-compatible boards captures mono audio from PDM and I²S
microphones and returns signed 16-bit PCM samples. It is tested on ESP32-S3
and also builds for RP2040/RP2350 through Arduino-Pico compatible cores.
The Arduino mbed RP2040 core is not supported. The library is compiled with
Arduino-ESP32 3.3.1 and with the UNIT Electronics Arduino-Pico core 3.1.0.

On ESP32, the PDM path uses the chip's hardware PDM-to-PCM converter, so
`read()` on PDM requires a target that has it, such as the ESP32-S3; the
ESP32-C6 does not include it. On RP2040/RP2350, the Arduino-Pico core
implements PDM input with PIO. The following table summarizes the functions
used with the UE0148.

| Function | Library call | Description |
|---|---|---|
| Initialization | `beginPDM(clkPin, dataPin, sampleRate, slot)` | Starts PDM capture on the selected pins. On ESP32, `slot` selects the receiver channel (`I2S_PDM_SLOT_LEFT` or `I2S_PDM_SLOT_RIGHT`). |
| Data acquisition | `read(buffer, samples, timeoutMs)` | Places mono signed 16-bit PCM samples in `buffer` and returns the number of samples read; returns 0 when no data arrives within the timeout. |
| Gain | `setGainPercent(percent)`, `getGainPercent()` | Scales PCM samples by 50 % to 800 %; 100 % leaves them unchanged. |
| Source status | `source()` | Reports whether the active input is PDM, I²S, or none. |
| Shutdown | `end()` | Stops capture so another source can start. |

The receiver slot is passed to `beginPDM()` and is not detected
automatically. It must match the microphone channel: the UE0148 default
(`CH` low) uses `I2S_PDM_SLOT_RIGHT`, while the library default is
`I2S_PDM_SLOT_LEFT`. The PDM clock is generated by the host peripheral, so
measuring `CLK` with a logic analyzer shows the sensor mode in use.

**Default values applied by the library**

| Parameter | Default value |
|---|---|
| Sample rate (ESP32) | 48 kHz |
| Receiver slot (ESP32) | Left (`I2S_PDM_SLOT_LEFT`) |
| Sample format | Signed 16-bit PCM, mono |
| Software gain | 100 % |
| `read()` timeout | 10 ms |

Use `setGainPercent()` to change the gain after `beginPDM()`.

**RP2040/RP2350 differences**

- `beginPDM(clkPin, dataPin, sampleRate)` takes no `slot` argument.
- The PDM examples use 8 kHz and 16 kHz sample rates; the library accepts rates
  up to 25 kHz.
- The Arduino-Pico core provides one global PDM instance, so only one PDM
  input can be active.

**Example sketches**

| Sketch | Source | Output |
|---|---|---|
| `AudioInputBasicRead` | [UE0148 repository](https://github.com/UNIT-Electronics-MX/unit_devlab_pdm_ics_41350_mems_microphone/blob/main/software/examples/pdm/cpp_examples/AudioInputBasicRead/AudioInputBasicRead.ino) | Absolute peak of each PCM16 block as text, 115200 baud (Section 5.2) |
| `LegacySerialStream` | [UE0148 repository](https://github.com/UNIT-Electronics-MX/unit_devlab_pdm_ics_41350_mems_microphone/blob/main/software/examples/pdm/cpp_examples/LegacySerialStream/LegacySerialStream.ino) | Binary PCM16 stream through the ESP32 I²S PDM driver, 2000000 baud |
| `BasicRead` | [Library `examples/PDM`](https://github.com/UNIT-Electronics-MX/unit_devlab_audioinput_library/tree/main/examples/PDM) | Peak level as text, 115200 baud |
| `SerialPlotter` | Library `examples/PDM` | Decimated samples as text, 115200 baud |
| `SerialSamples` | Library `examples/PDM` | Every PCM16 sample as text, 8 kHz, 115200 baud |
| `SerialStream` | Library `examples/PDM` | PCM16 mono, 48 kHz on ESP32-S3 or 8 kHz on RP, 2000000 baud |
| `ComputerAudio` | Library `examples/PDM` | PCM16 mono, 16 kHz, 921600 baud, played by `pc_audio.py` |

Section 5.3 describes the streaming protocol and the computer playback script.

### **3.7 Board Topology**

The released topology drawing locates the microphone (MK1), regulator (U3),
indicator LED (D1), edge connections (J1), four-position connector (J2), and
solder options on the top and bottom sides of the board.

![UE0148 PDM ICS-41350 top and bottom board topology.](hardware/resources/unit_topology_v_1_2_1_devlab_pdm_ics_41350_mems_microphone.png){width=6.3in}

### **3.8 Electrical Schematic**

The complete V1.1 schematic, covering the microphone, power supply,
connector, channel selection, and indicator circuits, appears in Section 9.4.
Use the original
[schematic PDF](https://unit-electronics-mx.github.io/unit_devlab_pdm_ics_41350_mems_microphone/hardware/unit_sch_v_1_2_1_ue0148_devlab_pdm_ics_41350_mems_microphone.pdf)
to inspect small component and net labels at full resolution.
