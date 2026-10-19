; Store and reload a byte using a label as its address.
        LDI 2A
        STA VALUE
        LDI 00
        LDA VALUE
        STA COPY
        OUT
        HLT
VALUE:  .BYTE 0
COPY:   .BYTE 0
