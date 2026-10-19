; Add two runtime nibbles and output their sum modulo 16.
        IN
        STA LEFT
        IN
        STA RIGHT
        LDA LEFT
        ADD RIGHT
        OUT
        HLT
LEFT:   .BYTE 0
RIGHT:  .BYTE 0
