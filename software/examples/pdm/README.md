# PDM Examples — UE0148

These Arduino C++ examples target an ESP32-S3. Connect board `CLK`
to host GPIO2, `DATA` to GPIO3, and `GND` to GND. Verify the
module's `VIN`/`VSYS` supply path and logic voltage against the
schematic or a measured board before applying power.

The UE0148 schematic shows `CH` pulled low, selecting the **right**
PDM channel. Both local examples select the right receiver slot. If
the assembled board selects left, change the receiver slot to
`I2S_PDM_SLOT_LEFT`.

| Sketch | Dependency | Serial output |
|---|---|---|
| [AudioInputBasicRead](cpp_examples/AudioInputBasicRead/README.md) | [DevLab_AudioInput](https://github.com/UNIT-Electronics-MX/unit_devlab_audioinput_library), Arduino-ESP32 3.x | Peak values at 115200 baud |
| [LegacySerialStream](cpp_examples/LegacySerialStream/README.md) | Arduino-ESP32 I²S PDM driver | Raw PCM16 at 2000000 baud |

The library reports ESP32-S3 hardware testing. Operation with this
exact UE0148 module still needs physical validation. See
[Board Operation](../../../tools/product-reference/chapters/05-board-operation.md)
for the full wiring table and checks.
