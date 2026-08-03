## **2 Electrical Characteristics**

### **2.1 ICS-41350 Characteristics**

The values in this section apply to the ICS-41350 sensor. They are not complete
module ratings.

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
| Regulated output | — | 3.3 V nominal | — | U3 identity from BOM; module behavior pending |

The permitted voltage at module `VIN`, the behavior and limits of `VSYS`, host
logic compatibility, and total module current are pending schematic
verification and module-level validation. Do not substitute the sensor VDD
range, the regulator limits, the diode ratings, or the connector rating for a
module input rating.

### **2.2 Electrical Precautions**

- Keep the host and module grounds connected during operation.
- Do not drive `DATA`; it is the microphone output.
- Apply `CLK` and `CH` only after the module power and logic domains have been
  verified against a released schematic or a measured board.
- Keep the bottom acoustic port free from debris, flux, adhesive, and enclosure
  obstruction.
- Verify `VIN`, `VSYS`, J2 supply routing, and solder-option states before first
  power-up.
