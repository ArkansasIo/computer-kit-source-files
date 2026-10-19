; Evaluate f(x)=x*x for x=3 using repeated addition. Output 9.
        LDI 3
        STA X
        LDI 0
        STA RESULT
        LDI 3
        STA COUNT
LOOP:   LDA RESULT
        ADD X
        STA RESULT
        LDA COUNT
        DEC
        STA COUNT
        JZ DONE
        JMP LOOP
DONE:   LDA RESULT
        OUT
        HLT
X:      .BYTE 0
RESULT: .BYTE 0
COUNT:  .BYTE 0
