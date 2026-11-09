## **3 Functional Overview**

The DevLab PDM ICS-41350 MEMS Microphone combines the TDK InvenSense
ICS-41350 digital microphone with a 3.3 V regulator and a channel-select
circuit. The microphone has no registers: the host supplies `CLK`, the
microphone returns a 1-bit pulse-density-modulated (PDM) stream on `DATA`, and
the `CLK` frequency alone selects the sensor mode.

The module does not produce audio samples by itself. A host with a PDM
receiver decimates and filters the bitstream into PCM audio.

### **3.1 Block Diagram** {.section-page}

The block diagram shows the main functional blocks of the UE0148 module and
the signals available.

![UE0148 PDM ICS-41350 microphone module block diagram.](hardware/resources/external/pdm_ics_41350_mems_microphone.png){width=6.3in}

The host drives `CLK`; the microphone drives `DATA` toward the host. `VIN`
feeds a 3.3 V regulator whose output reaches the microphone through the
`VSYS` rail.

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
`VIN`. Its output passes through the Schottky diode D2 to
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
mode.

### **3.6 Library Features**

The [DevLab_AudioInput](https://github.com/UNIT-Electronics-MX/unit_devlab_audioinput_library)
library for Arduino-compatible boards captures mono audio from PDM and I²S
microphones and returns signed 16-bit PCM samples.

PDM capture depends on the PDM receiver of the host board. For example, the
ESP32-S3 includes a hardware PDM-to-PCM converter, while the ESP32-C6 does not.
The following table summarizes the functions used with the UE0148.

| Function | Library call | Description |
|---|---|---|
| Initialization | `beginPDM(clkPin, dataPin, sampleRate, slot)` | Starts PDM capture on the selected pins and returns `true` on success. Returns `false` if another source is already active (call `end()` first), the board has no PDM-to-PCM converter, or initialization fails. `slot` selects the receiver channel (`I2S_PDM_SLOT_LEFT` or `I2S_PDM_SLOT_RIGHT`). |
| Data acquisition | `read(buffer, samples, timeoutMs)` | Places mono signed 16-bit PCM samples in `buffer` and returns the number of samples read; returns 0 when no data arrives within the timeout. |
| Gain | `setGainPercent(percent)`, `getGainPercent()` | Scales PCM samples by 50 % to 800 %; values outside this range are limited to it. 100 % leaves the samples unchanged, and the scaled result is clipped to the signed 16-bit range. |
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
| Sample rate | 48 kHz |
| Receiver slot | Left (`I2S_PDM_SLOT_LEFT`) |
| Sample format | Signed 16-bit PCM, mono |
| Software gain | 100 % |
| `read()` timeout | 10 ms |

Use `setGainPercent()` to change the gain after `beginPDM()`.

**Example sketches**

| Sketch | Source | Output |
|---|---|---|
| `AudioInputBasicRead` | [UE0148 repository](https://github.com/UNIT-Electronics-MX/unit_devlab_pdm_ics_41350_mems_microphone/blob/main/software/examples/pdm/cpp_examples/AudioInputBasicRead/AudioInputBasicRead.ino) | Absolute peak of each PCM16 block as text, 115200 baud |
| `LegacySerialStream` | [UE0148 repository](https://github.com/UNIT-Electronics-MX/unit_devlab_pdm_ics_41350_mems_microphone/blob/main/software/examples/pdm/cpp_examples/LegacySerialStream/LegacySerialStream.ino) | Binary PCM16 stream through the ESP32 I²S PDM driver, 2000000 baud |
| `BasicRead` | [Library `examples/PDM`](https://github.com/UNIT-Electronics-MX/unit_devlab_audioinput_library/tree/main/examples/PDM) | Peak level as text, 115200 baud |
| `SerialPlotter` | Library `examples/PDM` | Decimated samples as text, 115200 baud |
| `SerialSamples` | Library `examples/PDM` | Every PCM16 sample as text, 8 kHz, 115200 baud |
| `SerialStream` | Library `examples/PDM` | PCM16 mono, 48 kHz, 2000000 baud |
| `ComputerAudio` | Library `examples/PDM` | PCM16 mono, 16 kHz, 921600 baud, played by `pc_audio.py` |

### **3.7 Board Topology**

The released topology drawing locates the microphone (MK1), regulator (U3),
indicator LED (D1), edge connections (J1), four-position connector (J2), and
solder options on the top and bottom sides of the board.

![UE0148 PDM ICS-41350 top and bottom board topology.](hardware/resources/unit_topology_v_1_2_1_devlab_pdm_ics_41350_mems_microphone.png){width=6.3in}

### **3.8 Electrical Schematic**

The complete V1.1 schematic, covering the microphone, power supply,
connector, channel selection, and indicator circuits, is available in the original
[schematic PDF](https://unit-electronics-mx.github.io/unit_devlab_pdm_ics_41350_mems_microphone/hardware/unit_sch_v_1_2_1_ue0148_devlab_pdm_ics_41350_mems_microphone.pdf),
which allows inspecting small component and net labels at full resolution.
