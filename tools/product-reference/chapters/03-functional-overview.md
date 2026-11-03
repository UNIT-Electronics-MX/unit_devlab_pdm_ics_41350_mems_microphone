## **3 Functional Overview**

### **3.1 Functional Block Diagram** {.section-page}

![UE0148 PDM ICS-41350 microphone module block diagram.](hardware/resources/external/pdm_ics_41350_mems_microphone.png){width=6.3in}

The diagram summarizes the microphone, channel selection, indicator, and
board power section. The host drives `CLK`; the microphone drives
`DATA` toward the host. Section 2 specifies the sensor supply range.

### **3.2 Signal Path**

Sound enters the ICS-41350 through its bottom acoustic port. A MEMS sensing
element and impedance-converter amplifier feed a fourth-order sigma-delta
modulator. The `DATA` pin carries its 1-bit PDM output. The host supplies
`CLK` and decimates and filters PDM to obtain audio samples. The
microphone outputs a PDM bitstream. The
[ICS-41350 datasheet](hardware/resources/external/ds-000047-ics-41350-datasheet.pdf)
describes this path in its functional block diagram and “Theory of Operation.”

### **3.3 Clock-Controlled Modes**

The sensor has no mode register. Its clock frequency selects the mode:

| Sensor mode | `CLK` frequency | Typical sensor current | Typical sensitivity |
|---|---:|---:|---:|
| Sleep | Below 200 kHz | 12 µA | No data output |
| Low power | 400–800 kHz | 185 µA | −26 dB FS |
| Standard | 1.0–3.3 MHz | 430 µA | −26 dB FS |
| High performance | 4.1–4.8 MHz | 650 µA | −32 dB FS |

The table lists **sensor** characteristics from DS-000047. The clock
ranges between listed modes lie outside the specified operating modes.
Below 200 kHz, `DATA` becomes high impedance. After a valid clock starts,
the microphone takes up to 20 ms to wake and settle.
High-performance mode supports ultrasonic capture up to 40 kHz only when
the host decimation filter and acoustic path also preserve that band.

### **3.4 PDM Channel and Shared Data**

The ICS-41350 `SELECT` pin low selects the right channel (DATA1); high
at sensor VDD selects the left channel (DATA2). Right-channel bits are
clocked on the rising edge and left-channel bits on the falling edge.
The microphone releases `DATA` outside its selected half-cycle, allowing
one left and one right microphone to share a data line and clock.
The sensor datasheet specifies a shared PDM data line without a pull-up
or pull-down.

The UE0148 schematic connects board `CH` to sensor `SELECT` through
R5 (0 Ω) and shows R3 (10 kΩ) pulling the selection low: the circuit selects
the **right** channel by default. The assembled solder option determines
the effective selection. The host PDM receiver selects the same channel as the
microphone. The four-position connector carries `CLK` and `DATA`, but
not `CH`; the board option controls channel selection through that connector.

### **3.5 Power and Host Interface**

The circuit routes `VIN` through an AP2112K-3.3V regulator and
a Schottky diode toward `VSYS`; the microphone VDD pin is on `VSYS`.
It includes a 100 nF capacitor at microphone VDD and an orange power LED.
The header and connector expose the `VSYS` rail.
The ICS-41350 VDD operating range of 1.65–3.63 V applies at the sensor pin;
the module supply path determines the voltage at that pin.

![](hardware/resources/unit_btm_v_1_2_1_devlab_pdm_ics_41350_mems_microphone.png){width=5.4in}
