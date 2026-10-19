#pragma once
#include <cstdint>
enum class Opcode:uint8_t{NOP=0x00,LDA=0x01,LDB=0x02,ADD=0x03,SUB=0x04,STA=0x05,JMP=0x06,JZ=0x07,JC=0x08,OUT=0x09,HLT=0x0A,LDI=0x0B,INC=0x0C,DEC=0x0D,AND=0x0E,OR=0x0F,XOR=0x10,NOT=0x11,IN=0x12};
inline bool takesOperand(Opcode o){switch(o){case Opcode::LDA:case Opcode::LDB:case Opcode::ADD:case Opcode::SUB:case Opcode::STA:case Opcode::JMP:case Opcode::JZ:case Opcode::JC:case Opcode::LDI:case Opcode::AND:case Opcode::OR:case Opcode::XOR:return true;default:return false;}}
