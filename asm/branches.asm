; Count down and branch when the zero flag is set.
        LDI 03
        STA COUNT
LOOP:   LDA COUNT
        DEC
        STA COUNT
        JZ DONE
        JMP LOOP
DONE:   LDA COUNT
        OUT
        HLT
COUNT:  .BYTE 0
