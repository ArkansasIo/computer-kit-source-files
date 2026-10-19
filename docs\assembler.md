# Assembler guide

Build with CMake from the repository root, then run `ttl8-as program.asm`. It writes `program.bin`, `program.hex`, and `program.lst`. Supply an output prefix as a second argument to choose another name.

Source accepts labels ending in `:`, one instruction or `.BYTE` per line, and semicolon comments. Mnemonics and labels are case-insensitive. Numeric operands support decimal, `0x` hex, `$` hex, `h` suffix hex, and bare hex containing A–F. All values and label addresses must fit in one byte. `.BYTE value` emits one byte. The assembler does not yet implement expressions, macros, sections, strings, or relocatable objects.

```asm
        LDI 12
        STA VALUE
        LDA VALUE
        OUT
        HLT
VALUE:  .BYTE 0
```

The lexer, parser, symbol table, instruction metadata, and object file are in `assembler/`. Output bytes are loaded at address zero by `ttl8-run`.

`IN` reads the next byte passed to `ttl8-run`. For example, assemble `programs/input_add.asm`, then run `ttl8-run programs/input_add.bin 3 5`; each `OUT` value prints as two-digit hexadecimal.
