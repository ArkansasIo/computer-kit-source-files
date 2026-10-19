; A tiny fixed-input calculator: outputs 7+5= C, then 7-5=2 (hex).
        LDI 7
        STA LEFT
        LDI 5
        STA RIGHT
        LDA LEFT
        ADD RIGHT
        OUT
        LDA LEFT
        SUB RIGHT
        OUT
        HLT
LEFT:   .BYTE 0
RIGHT:  .BYTE 0
