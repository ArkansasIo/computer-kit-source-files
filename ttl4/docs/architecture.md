# TTL4 architecture

TTL4 uses a four-bit data path and an eight-bit program counter/address path. It has byte-wide program ROM and separate RAM with 256 four-bit cells. Instructions use the TTL8 opcode byte encoding to retain source compatibility, while `LDI` accepts only 0–F and all ALU results wrap modulo 16.

| Component | Purpose | Source |
|---|---|---|
| A and B registers | Hold 4-bit values | `cpu/Register4.hpp` |
| IR and MAR | Hold 8-bit opcode/operand/address bytes | `cpu/ByteRegister.hpp` |
| ALU | 4-bit add/subtract/logic and flags | `cpu/ALU4.hpp` |
| Data bus | Carries 4-bit values | `cpu/Bus4.hpp` |
| PC | 8-bit next-byte address | `cpu/CPU4.hpp` |
| Program ROM | 256 byte-wide locations | `cpu/CPU4.hpp` |
| RAM | 256 4-bit locations | `cpu/Memory4.hpp` |
| Control decoder | Validates opcode range | `cpu/ControlUnit4.hpp` |
| Input port | FIFO of 4-bit values consumed by `IN` | `cpu/InputPort4.hpp` |
| Output port | Captures each 4-bit value written by `OUT` | `cpu/OutputPort4.hpp` |

See the [hardware notes](hardware.md) and [UML diagrams](uml/).
