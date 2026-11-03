# LegacySerialStream

This older sketch uses the ESP32 I²S PDM driver directly. It captures
48 kHz mono PCM16 and sends little-endian binary samples at 2000000
baud after a `RAW` line. Send `R` to repeat the header or
`G200\n` to set software gain to 200%.

## Requirements

- ESP32-S3 board with Arduino-ESP32 3.x
- UE0148 wired as described in the [PDM example index](../../README.md)

## Run

1. Open [LegacySerialStream.ino](LegacySerialStream.ino) in Arduino IDE.
2. Select the ESP32-S3 board and upload the sketch.
3. Use a serial receiver configured for binary PCM16 mono, 48 kHz,
   little-endian, at 2000000 baud. A text Serial Monitor cannot play
   the binary stream.

The sketch selects the board's default right channel. If `CH` is
changed to left, set `PDM_MIC_SLOT` to `I2S_PDM_SLOT_LEFT`.
This is a legacy driver example; use AudioInputBasicRead for the
shared library API.
