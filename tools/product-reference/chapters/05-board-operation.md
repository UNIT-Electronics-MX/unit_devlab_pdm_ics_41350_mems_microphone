## **5 Board Operation**

No firmware example has been validated for this module, so this reference does
not present host code as a tested procedure.

For initial bench validation:

1. Inspect the board and ensure the bottom acoustic port is unobstructed.
2. Verify the `VIN`/`VSYS` power path, supply range, and logic domain against a
   released schematic or measured board.
3. Connect host and module grounds.
4. Connect the host PDM clock output to `CLK` and PDM data input to `DATA`.
5. Configure the channel only after verifying how board `CH` and the solder
   option connect to the ICS-41350 `SELECT` pin.
6. Apply a clock in the intended ICS-41350 mode range and verify timing with a
   logic analyzer before relying on captured samples.

Host GPIO numbers are controller-specific and are not module pin numbers.
Tested decimation settings, sample rates, host mappings, and module-level logic
limits remain pending validation.
