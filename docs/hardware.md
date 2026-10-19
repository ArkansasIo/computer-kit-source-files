# Hardware and component notes

This document describes functional blocks, not a verified schematic or bill of materials. Choose the exact logic family, voltage, clock rate, EEPROM wiring, and output driver from the physical build. TTL and CMOS parts can have different voltage and loading limits; check the selected component data sheets before connecting them.

## Datapath blocks

- **A and B registers:** hold ALU operands. A is the destination for arithmetic and logic results. B is currently only loadable; the current ISA does not use it in ALU operations.
- **ALU:** performs 8-bit add, subtract and bitwise functions. It produces a zero result indicator and a carry/borrow indicator for arithmetic.
- **Shared bus:** moves one byte between registers, ALU, memory and output. A physical bus needs controlled drivers so two sources are not enabled together.
- **Program counter and MAR:** PC points to the next byte; MAR holds a memory address during a read or write.
- **Memory:** 256 addressable bytes. The current model uses one RAM array for instructions and data, so programs can overwrite themselves.
- **Output port:** captures A on `OUT`. A physical LED display or header may need buffering/current-limiting components appropriate to its load.
- **Input port:** presents an 8-bit value to the CPU on `IN`. The emulator accepts a FIFO of values on the `ttl8-run` command line; a physical version needs a defined source such as switches or a serial interface and appropriate input conditioning.

## Control blocks

- **Instruction register and decoder:** capture the opcode and select its control sequence.
- **Flags:** retain zero and carry/borrow results for conditional branches.
- **Clock and reset:** sequence register transfers and establish known initial state. The software `Clock` helper is not an electrical oscillator or debouncer.
- **Control EEPROM:** stores control words indexed by opcode and microstep. Its address wiring, data width, polarity, reset sequence and timing must match the hardware definition passed to the microcode generator.

Before programming the EEPROM, document every control signal, bit position, active polarity, microstep count and mutually exclusive bus source. Then encode a representative instruction and inspect its control words against the schematic.
