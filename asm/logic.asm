; Bitwise operators use A and the byte stored at an address.
        LDI F0
        STA MASK
        LDI 0F
        OR MASK
        OUT
        LDI FF
        XOR MASK
        OUT
        LDI 55
        AND MASK
        NOT
        OUT
        HLT
MASK:   .BYTE 0
