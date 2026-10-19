# TTL8 instruction set

All values and addresses are 8 bits. Instructions are one opcode byte followed by zero or one operand byte. The opcode values are defined in `assembler/Instruction.hpp`.

| Opcode | Mnemonic | Bytes | Behavior |
|---:|---|---:|---|
| 00 | NOP | 1 | No operation |
| 01 | LDA addr | 2 | A ← RAM[addr], update Z |
| 02 | LDB addr | 2 | B ← RAM[addr] |
| 03 | ADD addr | 2 | A ← A + RAM[addr], C on overflow, update Z |
| 04 | SUB addr | 2 | A ← A − RAM[addr], C on borrow, update Z |
| 05 | STA addr | 2 | RAM[addr] ← A |
| 06 | JMP addr | 2 | PC ← addr |
| 07 | JZ addr | 2 | If Z, PC ← addr |
| 08 | JC addr | 2 | If C, PC ← addr |
| 09 | OUT | 1 | Send A to output port |
| 0A | HLT | 1 | Halt execution |
| 0B | LDI value | 2 | A ← value, update Z |
| 0C | INC | 1 | A ← A + 1 modulo 256, update Z |
| 0D | DEC | 1 | A ← A − 1 modulo 256, update Z |
| 0E | AND addr | 2 | A ← A AND RAM[addr], update Z |
| 0F | OR addr | 2 | A ← A OR RAM[addr], update Z |
| 10 | XOR addr | 2 | A ← A XOR RAM[addr], update Z |
| 11 | NOT | 1 | A ← bitwise NOT A, update Z |
| 12 | IN | 1 | A ← next queued input byte, update Z |

Flags not listed as changed are preserved. SUB's carry flag means borrow, as in the existing ALU implementation. INC and DEC do not set carry. These semantics are the software contract; confirm them against the physical control logic before wiring conditional flags.
