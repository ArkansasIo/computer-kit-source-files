; Reference control sequencing, not a programmed EEPROM image. Each instruction
; fetches opcode at T0 and increments PC; operand instructions fetch at T1.
; Control word bit assignments are hardware-specific and must be mapped to
; the actual TTL datapath before generating EEPROM bytes.
;
; T0: PC -> address bus, MEM_READ, IR_LOAD, PC_INC
; LDI T1: PC -> address bus, MEM_READ -> A, PC_INC
; LDA T1: PC -> MAR, PC_INC
; LDA T2: MAR -> address bus, MEM_READ -> A
; STA T1: PC -> MAR, PC_INC
; STA T2: A -> address bus, MEM_WRITE
; ADD T1/T2: fetch address; read memory operand
; ADD T3: ALU_ADD, A_LOAD, FLAGS_LOAD
; JMP T1: PC <- operand
; JZ/JC T1: fetch target; conditionally load PC
; HLT T0: HALT
; IN T0: INPUT_PORT -> A, FLAGS_LOAD, wait/ready handshake as required
