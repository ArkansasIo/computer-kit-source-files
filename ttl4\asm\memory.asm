        LDI A
        STA VALUE
        LDA VALUE
        STA COPY
        OUT
        HLT
VALUE:  .BYTE 0
COPY:   .BYTE 0
