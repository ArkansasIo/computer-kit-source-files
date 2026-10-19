; Emits the low byte sequence 0, 1, 1, 2, 3, ... forever (wraps at 255).
        LDI 00
        STA A
        LDI 01
        STA B
LOOP:   LDA A
        OUT
        ADD B
        STA TEMP
        LDA B
        STA A
        LDA TEMP
        STA B
        JMP LOOP
A:      .BYTE 0
B:      .BYTE 0
TEMP:   .BYTE 0
