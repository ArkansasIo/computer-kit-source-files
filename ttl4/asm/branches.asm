        LDI 3
        STA COUNT
LOOP:   LDA COUNT
        OUT
        DEC
        STA COUNT
        JZ DONE
        JMP LOOP
DONE:   HLT
COUNT:  .BYTE 0
