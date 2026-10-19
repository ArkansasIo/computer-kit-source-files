# TTL4 instruction set

TTL4 uses the same opcode numbers and mnemonics as TTL8 (`assembler/Instruction.hpp`). `LDA`, `LDB`, `ADD`, `SUB`, `STA`, `JMP`, `JZ`, `JC`, `AND`, `OR`, and `XOR` take an 8-bit address operand. `LDI` takes a four-bit immediate. `.BYTE` data must fit 0–F. Register and RAM writes retain only the low four bits.

`IN` reads the next queued 4-bit input value into A and updates zero. `OUT` appends A to the output-port history. Run with input values after the binary filename, such as `ttl4-run input_add.bin 3 5`.

ADD sets carry on overflow past F. SUB sets carry on borrow. Loads and ALU operations update zero; INC/DEC wrap modulo 16 and update zero without changing carry. Branches preserve flags. Other flag behavior matches TTL8. Opcode bytes follow `assembler/Instruction.hpp`.
