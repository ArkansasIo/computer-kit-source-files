# TTL8 architecture

TTL8 is an 8-bit accumulator computer with a 256-byte address space. Its current C++ implementation is an instruction-level reference model: one call to `CPU::step()` fetches and executes one complete instruction. It does not model electrical timing, tri-state bus contention, or EEPROM access delays.

## Main parts

| Part | Role | Current software model |
|---|---|---|
| A accumulator | Main ALU input/result register | `Register8` in `cpu/CPU.hpp` |
| B register | Secondary data register loaded by `LDB` | `Register8` |
| Program counter | Address of next instruction/operand | 8-bit field in CPU; reusable `ProgramCounter` component |
| Instruction register | Holds fetched opcode | `Register8` |
| MAR | Holds an address during a memory operation | `Register8` |
| ALU | 8-bit arithmetic and bitwise operations | `ALU` |
| Flags | Carry/borrow and zero status | CPU fields; reusable `Flags` component |
| RAM | 256 bytes, shared by code and data | `Memory` |
| Output port | Captures values written by `OUT` | output register and output history in CPU |
| Input port | FIFO of bytes consumed by `IN` | `InputPort` queue in CPU |
| Control unit/store | Decodes opcodes or stores per-step control words | `ControlUnit`, `ControlStore` |
| Clock | Drives sequential state transitions | `Clock` helper; not yet wired into `CPU::step()` |

The physical computer can be split into a datapath (registers, ALU, buses and RAM) and a control path (instruction decode, flags, program counter and microcode). See [hardware notes](hardware.md) and the [UML diagrams](uml/).

## Instruction flow

An instruction fetch reads RAM at PC into IR and increments PC. Instructions with an operand fetch that byte next. Address operands access the shared 256-byte memory. Arithmetic and logic operations update A; `OUT` copies A to the output port. Conditional branches inspect flags set by earlier operations. The detailed encoding is in [isa.md](isa.md).

## Software tools

`ttl8-as` translates assembly source into a raw binary image, hex bytes, and a listing. `ttl8-run` loads a binary image into the CPU reference model and prints each output byte. The microcode script encodes an explicit hardware signal map; it intentionally does not guess the bit positions for a particular breadboard.
