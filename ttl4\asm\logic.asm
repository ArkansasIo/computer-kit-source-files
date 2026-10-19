        LDI F
        STA MASK
        LDI 5
        AND MASK
        OUT
        LDI 5
        XOR MASK
        OUT
        HLT
MASK:   .BYTE 0
