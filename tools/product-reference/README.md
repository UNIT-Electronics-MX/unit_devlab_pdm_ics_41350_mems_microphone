# Product reference build

The product reference source is maintained in Markdown under `chapters/`. Document
metadata and chapter order are defined in `book.yml`.

## Local build

Requirements:

- Pandoc
- WeasyPrint

Run from the repository root:

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

The Markdown chapters are the source of truth. Product values and pin mappings
must be taken from the released files in `hardware/`, the manufacturing
BOM, or the supplied ICS-41350 datasheet. Do not infer module electrical
limits from the rating of an individual BOM component.

This edition omits unvalidated firmware and marks missing module-level
characteristics as pending.
