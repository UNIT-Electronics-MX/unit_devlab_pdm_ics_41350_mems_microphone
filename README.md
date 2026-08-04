# DevLab: PDM ICS-41350 MEMS Microphone Module
<!-- Exception:

The PULSAR development board line does not use the DevLab: prefix.

Format: PULSAR [MCU/Model]

Examples: PULSAR C6, PULSAR H2, PULSAR RP2350

The JUN R3 board also does not use DevLab:

Example: JUN R3 -->

## Introduction

The DevLab PDM ICS-41350 MEMS Microphone is a digital audio module built around
the bottom-port TDK InvenSense ICS-41350. The microphone provides a 1-bit PDM
output and supports low-power, standard, high-performance, and sleep modes
selected by the clock frequency. The BOM identifies an onboard 3.3 V regulator
and indicator LED; the artwork shows channel selection, six castellated
connections, and a four-position 1.0 mm-pitch connector.

<div align="center">
  <img src="hardware/resources/unit_top_v_1_1_0_pdm_ics_41350_mems_microphone.png" width="450px" alt="DevLab PDM ICS-41350 MEMS Microphone top view">
  <p><em>DevLab PDM ICS-41350 MEMS Microphone</em></p>
</div>

<div align="center">

### Quick Setup

[<img src="https://img.shields.io/badge/Product%20Wiki-blue?style=for-the-badge" alt="Product Wiki">](https://wiki.uelectronics.com/)
[<img src="https://img.shields.io/badge/Datasheet-green?style=for-the-badge" alt="Datasheet">](https://www.invensense.tdk.com/en-us/products/microphone/ics-41350)
[<img src="https://img.shields.io/badge/Buy%20Now-orange?style=for-the-badge" alt="Buy Now">](https://uelectronics.com/)
[<img src="https://img.shields.io/badge/Getting%20Started-purple?style=for-the-badge" alt="Getting Started">](https://github.com/UNIT-Electronics-MX/unit_devlab_pdm_ics_41350_mems_microphone/blob/main/hardware/README.md)

</div>

<div align="center">

## Overview

| Feature | Description |
|---|---|
| Product | DevLab PDM ICS-41350 MEMS Microphone |
| Manufacturer Part Number | UE0148 |
| Hardware Revision | V1.1 artwork |
| Microphone | TDK InvenSense ICS-41350 bottom-port digital MEMS microphone |
| Input Voltage `VIN` | 5V - 3.3V |
| Supply Current | 225uA Max |
| Sleep Current | 12uA |
| Sensitivity | -26 dB FS |
| SNR | 63 dBA |
| Dynamic Range | 89 dB |
| PSR | -97 dB FS |
| THD | 0.2% |
| Interface | 1-bit pulse-density modulation (PDM) |
| Exposed Signals | `GND`, `VIN`, `VSYS`, `CLK`, `DATA`, `CH` |
| Regulator | AP2112K-3.3TRG1 fixed 3.3 V LDO, as identified by the BOM |
| Connectors | 1×6 2.54 mm header footprint and 4-position 1.0 mm-pitch connector |
| Validation Status | Dimensions, and solder-option defaults pending validation |

</div>

## Applications

- Voice capture and voice-recognition prototypes
- Microphone arrays
- Camera and security or surveillance audio
- Low-power ambient sound analysis and keyword-spotting prototypes
- Ultrasonic sensing experiments using the ICS-41350 high-performance mode

## Resources

- [Schematic Diagram](https://github.com/UNIT-Electronics-MX/unit_devlab_pdm_ics_41350_mems_microphone/blob/main/hardware/README.md#hardware) — pending schematic verification
- [Pinout Diagram](https://github.com/UNIT-Electronics-MX/unit_devlab_pdm_ics_41350_mems_microphone/blob/main/hardware/README.md#pinout) — artwork-backed pin table
- [Getting Started Guide](https://github.com/UNIT-Electronics-MX/unit_devlab_pdm_ics_41350_mems_microphone/blob/main/hardware/README.md)
- [ICS-41350 Datasheet](https://www.invensense.tdk.com/en-us/products/microphone/ics-41350)

## 📝 License

All hardware and documentation in this project are licensed under the **MIT
License**. See the [repository license](https://github.com/UNIT-Electronics-MX/unit_devlab_pdm_ics_41350_mems_microphone/blob/main/LICENSE)
for details. Third-party reference files may have separate terms.

## Note of Development

This product documentation is under active development. The V1.1 artwork and
manufacturing BOM establish the visible pin labels and fitted component
identities; module-level electrical limits, dimensions, schematic topology,
and tested host configurations remain pending validation.

<div align="center">
  <sub>Template created by UNIT Electronics</sub>
</div>
