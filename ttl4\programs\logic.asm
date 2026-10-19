; Boolean operations on 4-bit values X=5 and Y=3.
; OUT sequence: AND=1, OR=7, XOR=6, NOT X=A.
        LDI 5
        STA X
        LDI 3
        STA Y
        LDA X
        AND Y
        OUT
        LDA X
        OR Y
        OUT
        LDA X
        XOR Y
        OUT
        LDA X
        NOT
        OUT
        HLT
X:      .BYTE 0
Y:      .BYTE 0
