; Add two runtime input bytes and output the result.
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
