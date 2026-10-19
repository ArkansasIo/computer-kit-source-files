# TTL4 computer kit project

This is a sibling 4-bit data-path version of the TTL8 project. Its accumulator, B register, ALU, data bus, RAM cells and output values are four bits wide (0–F). The program counter and memory address are 8 bits, allowing 256 locations. It uses byte-wide program ROM and a separate 256 x 4-bit data RAM. Instructions and assembler object files retain the shared opcode encoding; operand bytes are addresses or 4-bit immediates as described in `docs/isa.md`. The assembler emits `.bin`, `.hex`, and byte-address `.lst` files. CPU component classes have header declarations and matching `.cpp` implementations, built as `ttl4-cpu`.

## Build and run

```sh
cmake -S . -B build
cmake --build build
build/ttl4-as programs/add.asm
build/ttl4-run programs/add.bin
```

On Windows, run the executable under `build/Debug/` or `build/Release/`. The emulator prints each `OUT` value as a hexadecimal nibble. The project includes the parallel `assembler/`, `cpu/`, `asm/`, `programs/`, `microcode/`, and `docs/` folders.

The emulator accepts runtime input values after the binary filename, for example `ttl4-run programs/input_add.bin 3 5`; output values are printed as hex nibbles. The control-store generator is shared with TTL8. Supply your actual hardware signal map; no physical EEPROM bit assignment is assumed. Math and logic assembly examples are listed in [docs/examples.md](docs/examples.md). See [all documentation](docs/README.md).
