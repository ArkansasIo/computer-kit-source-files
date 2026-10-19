# TTL8 assembler and CPU model

This repository provides a small C++17 assembler and an executable reference model for the 8-bit TTL CPU instruction set. The assembler turns source into raw machine-code bytes (`.bin`), space-separated hexadecimal (`.hex`), and a byte-address listing (`.lst`). CPU classes are declared in `cpu/*.hpp` and implemented in matching `.cpp` files. The model is instruction-level, not a cycle-accurate electrical simulation.

`assembler/` also contains reusable token, lexer, parser, symbol-table, instruction, and object-file components. CPU and object-file class declarations are in headers, with their implementations in matching `.cpp` files; CMake compiles them into the `ttl8-cpu` library. `asm/` contains focused language examples; `programs/` contains runnable sample programs.

Project layout and component documentation are in [docs/README.md](docs/README.md). UML diagrams are in [docs/uml/](docs/uml/).

The sibling [TTL4 project](ttl4/README.md) contains a matching 4-bit data-path version with its own assembler, emulator, sample programs, hardware notes, and UML diagrams.

To build both projects and compare the same `3 + 5` program, run `./run-both.ps1` from PowerShell. It prints the TTL8 and TTL4 output values side by side.

## Build and assemble

```sh
cmake -S . -B build
cmake --build build
build/ttl8-as programs/add.asm
```

On Windows the executable is `build/Debug/ttl8-as.exe` or `build/Release/ttl8-as.exe`. Pass a second argument to choose the output prefix: `ttl8-as input.asm out/demo`.

Run a binary and print each `OUT` byte as two-digit hexadecimal with `ttl8-run out/demo.bin`. Supply values consumed by `IN` as additional arguments, for example `ttl8-run input_add.bin 3 5`.

## Assembly syntax

One instruction or `.BYTE` directive per line. Labels end with `:` and are case-insensitive. A semicolon starts a comment. Operands can be decimal, hexadecimal (`0x14`, `$14`, `14h`, or bare hex containing A–F), or a label. All addresses and values are one byte; memory has 256 bytes. `.BYTE` reserves/emits one byte. There are no expressions, strings, sections, or relocations yet.

Example:

```asm
        LDI 12
        STA VALUE
        LDA VALUE
        OUT
        HLT
VALUE:  .BYTE 0
```

The listed opcodes are encoded as defined in `assembler/Instruction.hpp`. Address operands for `LDA`, `LDB`, `ADD`, `SUB`, `STA`, `JMP`, `JZ`, `JC`, `AND`, `OR`, and `XOR` use one byte; `LDI` takes an immediate byte.

## CPU semantics

`LDA addr` loads A from memory; `LDB addr` loads B. Arithmetic and logic instructions operate on A and a memory operand, except `NOT`, `INC`, and `DEC`, which operate on A. `STA addr` stores A. `IN` reads the next byte from the input FIFO; `OUT` appends A to the output port history. `JZ` tests the zero flag and `JC` tests carry. ADD sets carry on overflow; SUB sets carry on borrow. Loads, arithmetic, logic, increment, decrement, and input update zero. Other operations preserve flags. `reset()` clears RAM, ports, and registers; `loadProgram()` loads bytes and sets PC to the supplied start address. `run()` stops on HLT or throws after its step limit.

## Hardware boundary

`microcode/microcode.asm` documents suggested control phases. `microcode/generate_microcode.py` encodes an explicit JSON signal map and instruction microsteps into a little-endian EEPROM image; no default bit map is supplied because the physical datapath's control-word layout and timing were not specified. Example input shape:

```json
 {"word_bits":16,"step_bits":3,
 "signals":{"PC_OUT":0,"IR_LOAD":1,"HALT":2},
 "instructions":{"00":[["PC_OUT","IR_LOAD"],["HALT"]]}}
```

Generate with `python microcode/generate_microcode.py definition.json control.rom --hex control.hex`. The C++ CPU model is an instruction-level reference; it does not model bus contention or clock phases.
