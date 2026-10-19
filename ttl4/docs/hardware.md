# TTL4 hardware components

TTL4 narrows the data path to four bits while retaining eight address lines. Functional blocks include A/B registers, a 4-bit ALU, 4-bit data bus, 8-bit program counter, byte-wide program ROM, 256x4 RAM, opcode decoder, flags, 4-bit input port, output latch, clock/reset and a control EEPROM. This is a logical block list, not a verified schematic or bill of materials.

The microcode generator requires the real signal-to-bit map, signal polarity, microstep count and ROM wiring. Confirm voltage compatibility, timing, bus-driver exclusivity and memory write behavior against the chosen component data sheets and schematic before building the physical circuit.
