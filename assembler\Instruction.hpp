#pragma once
#include <cstdint>
#include <string>
#include <unordered_map>

enum class Opcode : uint8_t { NOP=0x00,LDA=0x01,LDB=0x02,ADD=0x03,SUB=0x04,STA=0x05,JMP=0x06,JZ=0x07,JC=0x08,OUT=0x09,HLT=0x0A,LDI=0x0B,INC=0x0C,DEC=0x0D,AND=0x0E,OR=0x0F,XOR=0x10,NOT=0x11,IN=0x12 };
struct InstructionInfo { Opcode opcode; int operandBytes; };
inline const std::unordered_map<std::string, InstructionInfo> InstructionSet = {
 {"NOP",{Opcode::NOP,0}},{"LDA",{Opcode::LDA,1}},{"LDB",{Opcode::LDB,1}},{"ADD",{Opcode::ADD,1}},{"SUB",{Opcode::SUB,1}},{"STA",{Opcode::STA,1}},{"JMP",{Opcode::JMP,1}},{"JZ",{Opcode::JZ,1}},{"JC",{Opcode::JC,1}},{"OUT",{Opcode::OUT,0}},{"HLT",{Opcode::HLT,0}},{"LDI",{Opcode::LDI,1}},{"INC",{Opcode::INC,0}},{"DEC",{Opcode::DEC,0}},{"AND",{Opcode::AND,1}},{"OR",{Opcode::OR,1}},{"XOR",{Opcode::XOR,1}},{"NOT",{Opcode::NOT,0}},{"IN",{Opcode::IN,0}}
};
