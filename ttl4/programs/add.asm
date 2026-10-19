; Hexadecimal 3 + 9 produces C.
        LDI 3
        STA NUM1
        LDI 9
        STA NUM2
        LDA NUM1
        ADD NUM2
        OUT
        HLT
NUM1:   .BYTE 0
NUM2:   .BYTE 0
