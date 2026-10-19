# TTL4 assembler

The C++17 assembler accepts the same labels, semicolon comments, numeric forms and `.BYTE` directive as TTL8. Addresses can use the full byte range; immediate and data values must fit in one nibble. It emits `.bin`, `.hex`, and `.lst` files. Build from this directory with CMake, then run `ttl4-as source.asm [output-prefix]`.

The current binary is the program ROM image. `.BYTE` bytes are emitted into that image and do not initialize the separate data RAM in the emulator. The included examples use zero-valued labels as RAM locations and initialize them with `STA` before reading.

The shared token, lexer, parser and symbol-table helpers are included beside the assembler. The current CLI uses its own compact two-pass line parser in `assembler/Assembler.cpp`.
