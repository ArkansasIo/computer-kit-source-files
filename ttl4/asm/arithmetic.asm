        LDI 7
        STA LEFT
        LDI 9
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
