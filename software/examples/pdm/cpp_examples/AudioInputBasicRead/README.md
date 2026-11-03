# AudioInputBasicRead

Reads the UE0148's default right PDM channel through
[DevLab_AudioInput](https://github.com/UNIT-Electronics-MX/unit_devlab_audioinput_library).
The library converts the input to mono PCM16 at 48 kHz. The sketch
prints the absolute peak of each 256-sample block at 115200 baud.

## Requirements

- ESP32-S3 board with Arduino-ESP32 3.x
- DevLab_AudioInput installed in the Arduino sketchbook
- UE0148 wired as described in the [PDM example index](../../README.md)

## Run

1. Open [AudioInputBasicRead.ino](AudioInputBasicRead.ino) in Arduino IDE.
2. Select the ESP32-S3 board and upload the sketch.
3. Open Serial Monitor at 115200 baud and make a sound near the microphone.
   The peak values should change with sound level.

The value is a PCM amplitude, not a calibrated sound-pressure level.
If `CH` selects left on the assembled board, use
`I2S_PDM_SLOT_LEFT` in the `beginPDM()` call. Capture with this
exact module has not been independently validated.
