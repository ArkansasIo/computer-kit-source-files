#pragma once
#include <cstdint>
enum class ControlOperation:uint8_t { Nop,Lda,Ldb,Add,Sub,Sta,Jmp,Jz,Jc,Out,Hlt,Ldi,Inc,Dec,And,Or,Xor,Not,In,Invalid };
class ControlUnit {
public:
 static ControlOperation decode(uint8_t opcode){switch(opcode){
 case 0x00:return ControlOperation::Nop;case 0x01:return ControlOperation::Lda;case 0x02:return ControlOperation::Ldb;case 0x03:return ControlOperation::Add;case 0x04:return ControlOperation::Sub;case 0x05:return ControlOperation::Sta;case 0x06:return ControlOperation::Jmp;case 0x07:return ControlOperation::Jz;case 0x08:return ControlOperation::Jc;case 0x09:return ControlOperation::Out;case 0x0A:return ControlOperation::Hlt;case 0x0B:return ControlOperation::Ldi;case 0x0C:return ControlOperation::Inc;case 0x0D:return ControlOperation::Dec;case 0x0E:return ControlOperation::And;case 0x0F:return ControlOperation::Or;case 0x10:return ControlOperation::Xor;case 0x11:return ControlOperation::Not;case 0x12:return ControlOperation::In;default:return ControlOperation::Invalid;}}
};
