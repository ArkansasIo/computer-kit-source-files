# UML diagrams

These PlantUML diagrams can be rendered with any PlantUML viewer.

- [Class diagram](class-diagram.puml) shows the CPU model and reusable hardware components.
- [System diagram](system-diagram.puml) shows the source-to-machine-code path and microcode generation path.

The lexer/parser/symbol-table decomposition is the intended toolchain design; the current assembler executable still parses source through its line-based implementation in `assembler/Assembler.cpp`. The class diagram marks component helpers that are not yet wired into `CPU`.
