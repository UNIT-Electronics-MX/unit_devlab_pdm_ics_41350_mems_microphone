# Product reference build

The product reference source is maintained in Markdown under `chapters/`. Document
metadata and chapter order are defined in `book.yml`.

## Board figures

Chapter 4 embeds the [UE0148 pinout](assets/ue0148-pinout.png) and
[UE0148 schematic](assets/ue0148-schematic.png) as images. The source
drawings remain in `hardware/`.

## Local build

Requirements:

- Pandoc
- WeasyPrint, XeLaTeX, or LibreOffice for PDF output

The repository root provides this build command:

```bash
./tools/product-reference/build.sh
```

Generated files are written to `build/product-reference/`:

```text
unit_product_reference_v_0_1_0_pdm_ics_41350_mems_microphone.md
unit_product_reference_v_0_1_0_pdm_ics_41350_mems_microphone.docx
unit_product_reference_v_0_1_0_pdm_ics_41350_mems_microphone.html
unit_product_reference_v_0_1_0_pdm_ics_41350_mems_microphone.pdf
```

The Markdown chapters define the product reference. Board values and pin
mappings follow the files in `hardware/`; ICS-41350 characteristics follow
the manufacturer datasheet. The sensor supply range applies at the
microphone pin.

Chapter 5 presents the ESP32-S3 capture example with the DevLab_AudioInput
library.
