```{=latex}
\clearpage
```

```{=openxml}
<w:p><w:r><w:br w:type="page"/></w:r></w:p>
```

## **4 Connectors and Pinout**

### **4.1 Pinout Diagram** {.section-page}

![](tools/product-reference/assets/ue0148-pinout.png){width=4.0in}

```{=latex}
\clearpage
```

```{=openxml}
<w:p><w:r><w:br w:type="page"/></w:r></w:p>
```

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
