#include "Assembler.hpp"
#include "Instruction.hpp"
#include <cctype>
#include <sstream>
#include <stdexcept>
#include <unordered_map>
#include <vector>
namespace {
struct Line { std::string op,arg; };
const std::unordered_map<std::string,Opcode> ops={{"NOP",Opcode::NOP},{"LDA",Opcode::LDA},{"LDB",Opcode::LDB},{"ADD",Opcode::ADD},{"SUB",Opcode::SUB},{"STA",Opcode::STA},{"JMP",Opcode::JMP},{"JZ",Opcode::JZ},{"JC",Opcode::JC},{"OUT",Opcode::OUT},{"HLT",Opcode::HLT},{"LDI",Opcode::LDI},{"INC",Opcode::INC},{"DEC",Opcode::DEC},{"AND",Opcode::AND},{"OR",Opcode::OR},{"XOR",Opcode::XOR},{"NOT",Opcode::NOT},{"IN",Opcode::IN}};
std::string trim(std::string s){auto a=s.find_first_not_of(" \t\r\n");if(a==s.npos)return{};auto b=s.find_last_not_of(" \t\r\n");return s.substr(a,b-a+1);}
std::string upper(std::string s){for(char& c:s)c=char(std::toupper(static_cast<unsigned char>(c)));return s;}
unsigned number(std::string s,const std::unordered_map<std::string,uint8_t>& syms){s=upper(trim(s));auto it=syms.find(s);if(it!=syms.end())return it->second;int base=10;if(s.rfind("0X",0)==0){s=s.substr(2);base=16;}else if(!s.empty()&&s[0]=='$'){s=s.substr(1);base=16;}else if(!s.empty()&&s.back()=='H'){s.pop_back();base=16;}else if(s.find_first_of("ABCDEF")!=s.npos)base=16;size_t n=0;unsigned long v=std::stoul(s,&n,base);if(n!=s.size()||v>255)throw std::runtime_error("invalid 8-bit operand: "+s);return unsigned(v);}
}
ObjectFile Assembler::assemble(const std::string& source){
 std::vector<Line> lines;std::unordered_map<std::string,uint8_t> symbols;std::istringstream in(source);std::string raw;unsigned pc=0;
 while(std::getline(in,raw)){auto c=raw.find(';');if(c!=raw.npos)raw.resize(c);raw=trim(raw);if(raw.empty())continue;auto colon=raw.find(':');if(colon!=raw.npos){auto label=upper(trim(raw.substr(0,colon)));if(label.empty()||symbols.count(label))throw std::runtime_error("invalid or duplicate label: "+label);if(pc>255)throw std::runtime_error("label outside memory range: "+label);symbols[label]=uint8_t(pc);raw=trim(raw.substr(colon+1));}Line line{};std::istringstream ss(raw);ss>>line.op;std::getline(ss,line.arg);line.op=upper(line.op);line.arg=trim(line.arg);if(!line.op.empty()){unsigned size;if(line.op==".BYTE")size=1;else{auto op=ops.find(line.op);if(op==ops.end())throw std::runtime_error("unknown instruction: "+line.op);size=1+(takesOperand(op->second)?1:0);if(takesOperand(op->second)!=!line.arg.empty())throw std::runtime_error("wrong operand count for "+line.op);}if(pc+size>256)throw std::runtime_error("program exceeds 256-byte address space");pc+=size;}lines.push_back(line);}
 ObjectFile obj;for(const auto& line:lines){if(line.op.empty())continue;if(line.op==".BYTE"){unsigned v=number(line.arg,symbols);if(v>15)throw std::runtime_error(".BYTE values must fit in four bits");obj.emit(uint8_t(v));continue;}Opcode op=ops.at(line.op);obj.emit(uint8_t(op));if(takesOperand(op)){unsigned v=number(line.arg,symbols);if(op==Opcode::LDI&&v>15)throw std::runtime_error("LDI immediate must fit in four bits");obj.emit(uint8_t(v));}}return obj;
}
