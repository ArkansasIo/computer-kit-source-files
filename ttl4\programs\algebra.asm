; Evaluate y=2x+3 for x=4. Output B (hexadecimal 11).
        LDI 4
        STA X
        LDI 3
        STA THREE
        LDA X
        ADD X
        ADD THREE
        OUT
        HLT
X:      .BYTE 0
THREE:  .BYTE 0
