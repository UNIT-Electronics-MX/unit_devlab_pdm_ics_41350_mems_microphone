# Software Examples — UE0148 PDM ICS-41350

The Arduino sketches follow one layout:

```text
pdm/
├── README.md
└── cpp_examples/
    ├── AudioInputBasicRead/
    │   ├── AudioInputBasicRead.ino
    │   └── README.md
    └── LegacySerialStream/
        ├── LegacySerialStream.ino
        └── README.md
```

Each sketch is in its own directory, and its `.ino` filename matches
the directory name so Arduino IDE can open it directly.

| Example | Purpose | Output |
|---|---|---|
| [AudioInputBasicRead](pdm/cpp_examples/AudioInputBasicRead/README.md) | Capture PDM through DevLab_AudioInput | PCM16 peak as text, 115200 baud |
| [LegacySerialStream](pdm/cpp_examples/LegacySerialStream/README.md) | Capture through the ESP32 driver | Binary PCM16 stream, 2000000 baud |

Start with [PDM wiring and setup](pdm/README.md). The complete procedure
and the library example are also in
[Board Operation](../../tools/product-reference/chapters/05-board-operation.md).
