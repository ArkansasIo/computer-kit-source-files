; 4-bit data-path demo: computes 3 + 9 = C.
        LDI 3
        STA 40
        LDI 9
        STA 41
        LDA 40
        ADD 41
        OUT
        HLT
