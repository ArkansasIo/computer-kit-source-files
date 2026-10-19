; Outputs 3, 2, 1, then halts. Values wrap in the range 0..15.
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
