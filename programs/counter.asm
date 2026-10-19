; Emits 0, 1, ... 9 then halts. JZ checks the zero flag after decrement.
        LDI 0A
        STA COUNT
LOOP:   LDA COUNT
        OUT
        LDA COUNT
        DEC
        STA COUNT
        JZ DONE
        JMP LOOP
DONE:   HLT
COUNT:  .BYTE 0
