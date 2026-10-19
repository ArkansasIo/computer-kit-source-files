; Computes 0x12 + 0x30 and writes the result to OUT.
        LDI 12
        STA NUM1
        LDI 30
        STA NUM2
        LDA NUM1
        ADD NUM2
        OUT
        HLT
NUM1:   .BYTE 0
NUM2:   .BYTE 0
