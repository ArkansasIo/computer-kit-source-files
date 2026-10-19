; Emits four Fibonacci values (0, 1, 1, 2) and halts. Arithmetic wraps mod 16.
        LDI 0
        STA A
        LDI 1
        STA B
        LDI 4
        STA COUNT
LOOP:   LDA A
        OUT
        ADD B
        STA TEMP
        LDA B
        STA A
        LDA TEMP
        STA B
        LDA COUNT
        DEC
        STA COUNT
        JZ DONE
        JMP LOOP
DONE:   HLT
A:      .BYTE 0
B:      .BYTE 0
TEMP:   .BYTE 0
COUNT:  .BYTE 0
