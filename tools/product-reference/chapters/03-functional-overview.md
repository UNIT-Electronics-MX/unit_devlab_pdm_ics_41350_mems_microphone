## **3 Functional Overview**

### **3.1 Audio Signal Path**

The ICS-41350 senses pressure through its bottom acoustic port and emits the
1-bit output of a fourth-order sigma-delta modulator on `DATA`. A host supplies
`CLK` and performs PDM decimation or passes the stream to a compatible codec.

### **3.2 Operating Modes**

The sensor selects its operating mode from the applied clock frequency: below
200 kHz for sleep, 400 to 800 kHz for low power, 1.0 to 3.3 MHz for standard,
and 4.1 to 4.8 MHz for high performance. These are ICS-41350 characteristics;
tested module and host configurations remain pending validation.

### **3.3 Channel Selection**

At the ICS-41350 `SELECT` pin, low selects the right channel (`DATA1`) and high,
tied to sensor VDD, selects the left channel (`DATA2`). The V1.1 board artwork
labels an exposed `CH` connection and a `CH SELECTION L/R` solder option. Their
exact circuit mapping and default state are pending schematic verification.

### **3.4 Power Section**

The BOM identifies an AP2112K-3.3TRG1 regulator, NSR0320MW2T1G Schottky diode,
1 µF power capacitors, a 100 nF microphone decoupling capacitor, an orange
indicator LED, and associated resistors. The exact `VIN`/`VSYS` path and the
LED-enable default remain pending schematic verification.

![](hardware/resources/unit_btm_v_1_1_0_pdm_ics_41350_mems_microphone.png){width=5.4in}
