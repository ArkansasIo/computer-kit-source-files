; Discrete calculus example: for f(x)=x^2, delta-f(x)=f(x+1)-f(x)=2x+1.
; At x=3, compute 2*3+1 and output 7 (hex).
        LDI 3
        STA X
        LDI 1
        STA ONE
        LDA X
        ADD X
        ADD ONE
        OUT
        HLT
X:      .BYTE 0
ONE:    .BYTE 0
