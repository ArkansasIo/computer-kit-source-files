; Minimal reset/startup sequence. CPU reset begins execution at address 0.
START:  LDI 00
        STA RESULT
        JMP MAIN
        .BYTE 00
MAIN:   HLT
RESULT: .BYTE 00
