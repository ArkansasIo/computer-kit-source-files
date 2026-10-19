; Demonstrates immediate load, addition, subtraction, carry and zero branches.
        LDI 200
        STA LEFT
        LDI 100
        STA RIGHT
        LDA LEFT
        ADD RIGHT
        JC CARRIED
        OUT
        HLT
CARRIED:
        OUT
        LDA LEFT
        SUB RIGHT
        OUT
        HLT
LEFT:   .BYTE 0
RIGHT:  .BYTE 0
