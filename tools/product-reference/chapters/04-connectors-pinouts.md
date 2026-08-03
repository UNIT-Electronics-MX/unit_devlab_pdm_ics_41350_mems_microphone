## **4 Connectors and Pinout**

### **4.1 Edge Connections**

| Board label | Direction | Function |
|---|---|---|
| `GND` | Power | Common ground |
| `VIN` | Input | Module power-section input; allowed range pending |
| `VSYS` | Power | Module system rail; electrical behavior pending |
| `CLK` | Input | PDM clock input |
| `DATA` | Output | PDM microphone data |
| `CH` | Input | Channel-selection signal; module mapping pending schematic verification |

### **4.2 Four-Position Connector**

The V1.1 top artwork labels the connector signals, from top to bottom in the
rendered view, as `CLK`, `DATA`, `VSYS`, and `GND`. The manufacturing BOM calls
J2 a four-position, 1.0 mm-pitch right-angle connector. Verify physical
orientation before connecting a cable; this edition does not assign connector
pin numbers.

### **4.3 Solder Options**

The bottom artwork identifies `CH SELECTION L/R` and `LED ON ENABLE` options.
Their default copper states and exact circuit connections are pending schematic
verification.
