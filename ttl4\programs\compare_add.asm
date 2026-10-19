; Shared TTL8/TTL4 comparison program: 3 + 5 = 8.
        LDI 3
        STA LEFT
        LDI 5
        STA RIGHT
        LDA LEFT
        ADD RIGHT
        OUT
        HLT
LEFT:   .BYTE 0
RIGHT:  .BYTE 0
