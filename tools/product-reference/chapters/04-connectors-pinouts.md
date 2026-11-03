## **4 Connectors and Pinout**

The released pinout shows both board views, the edge labels, and the
four-position connector signals. English and Spanish PDFs are linked in
Section 8.

![UE0148 pinout, top and bottom views.](hardware/resources/unit_pinout_v_1_2_1__devlab_pdm_ics_41350_mems_microphone_en.png){width=5.0in}

### **4.1 Edge Connections**

| Board label | Direction | Function |
|---|---|---|
| `GND` | Power | Common ground |
| `VIN` | Input | Regulator input |
| `VSYS` | Power | System rail supplying the microphone |
| `CLK` | Input | PDM clock input |
| `DATA` | Output | PDM microphone data |
| `CH` | Input | Connects to ICS-41350 `SELECT` through R5; low selects right, high selects left |

### **4.2 Four-Position Connector**

The V1.1 top artwork labels the connector signals, from top to bottom in the
rendered view, as `CLK`, `DATA`, `VSYS`, and `GND`. J2 is a four-position,
1.0 mm-pitch right-angle connector. The board pinout shows signal order
by physical position.

### **4.3 Solder Options**

The bottom artwork identifies `CH SELECTION L/R` and `LED ON ENABLE` options.
R3 pulls channel selection low, so the default channel is right. The
assembled solder bridges determine channel selection and LED operation.
