## **4 Connectors and Pinout**

The released pinout shows both board views, the edge labels, and the
four-position connector signals. English and Spanish PDFs are linked in
Section 8.

### **4.1 Pinout Diagram** {.section-page}

![UE0148 pinout showing the top and bottom board views and connector signals.](tools/product-reference/assets/ue0148-pinout.png){width=5.0in}

### **4.2 Edge Connections**

| Board label | Direction | Function |
|---|---|---|
| `GND` | Power | Common ground |
| `VIN` | Input | Regulator input |
| `VSYS` | Power | System rail supplying the microphone |
| `CLK` | Input | PDM clock input |
| `DATA` | Output | PDM microphone data |
| `CH` | Input | Connects to ICS-41350 `SELECT` through R5; low selects right, high selects left |

### **4.3 Four-Position Connector**

The V1.1 top artwork labels the connector signals, from top to bottom in the
rendered view, as `CLK`, `DATA`, `VSYS`, and `GND`. J2 is a four-position,
1.0 mm-pitch right-angle connector. The board pinout shows signal order
by physical position.

### **4.4 Solder Options**

The bottom artwork identifies `CH SELECTION L/R` and `LED ON ENABLE` options.
R3 pulls channel selection low, so the default channel is right. The
assembled solder bridges determine channel selection and LED operation.

```{=latex}
\clearpage
```

```{=openxml}
<w:p><w:r><w:br w:type="page"/></w:r></w:p>
```

### **4.5 Board Schematic** {.section-page}

The UE0148 schematic shows the microphone, power supply, connector,
channel selection, and indicator circuits.

![UE0148 PDM ICS-41350 board schematic.](tools/product-reference/assets/ue0148-schematic.png){width=6.4in}

```{=latex}
\clearpage
```

```{=openxml}
<w:p><w:r><w:br w:type="page"/></w:r></w:p>
```
