## **2 Electrical Characteristics**

### **2.1 ICS-41350 Characteristics**

The electrical table specifies ICS-41350 sensor characteristics. The
module power circuit includes a fixed 3.3 V regulator.

| Parameter | Low-power mode | Standard mode | High-performance mode | Scope |
|---|---:|---:|---:|---|
| Clock frequency | 400–800 kHz | 1.0–3.3 MHz | 4.1–4.8 MHz | Sensor `CLK` |
| Sensitivity, typical | −26 dB FS | −26 dB FS | −32 dB FS | Sensor, 1 kHz and 94 dB SPL |
| SNR, typical | 63 dBA | 64 dBA | 64 dBA | Sensor |
| Supply current, typical | 185 µA | 430 µA | 650 µA | Sensor at VDD = 1.8 V, no load |
| Acoustic overload point, typical | 120 dB SPL | 120 dB SPL | 126 dB SPL | Sensor, 10% THD |

| Parameter | Minimum | Typical | Maximum | Scope |
|---|---:|---:|---:|---|
| Sensor supply voltage, VDD | 1.65 V | — | 3.63 V | ICS-41350 supply pin |
| Sleep-mode clock | — | — | Below 200 kHz | ICS-41350 `CLK` |
| Sleep current | — | 12 µA | 20 µA | ICS-41350 |
| Digital input high, VIH | 0.65 × VDD | — | — | ICS-41350 digital input |
| Digital input low, VIL | — | — | 0.35 × VDD | ICS-41350 digital input |
| Regulated output | — | 3.3 V nominal | — | AP2112K-3.3 regulator |

The sensor VDD range applies at the microphone supply pin. The module
routes `VIN` through its regulator and Schottky diode to `VSYS`, which
supplies the microphone. The schematic defines the module power path;
the sensor VDD range does not specify a module `VIN` input range.

### **2.2 Electrical Precautions**

- The host and module share a common ground during operation.
- The microphone drives `DATA` toward the host.
- The host applies `CLK` and `CH` within the powered microphone's logic domain.
- The bottom acoustic port remains clear of debris, flux, adhesive, and
  enclosure obstructions.
- The board schematic shows the `VIN` to `VSYS` supply path and the J2 power
  connection.
