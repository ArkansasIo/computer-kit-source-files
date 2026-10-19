#include "Assembler.hpp"
#include <algorithm>
#include <cctype>
#include <iomanip>
#include <sstream>
#include <stdexcept>
namespace {
std::string trim(std::string s){auto a=s.find_first_not_of(" \t\r\n");if(a==s.npos)return {};auto b=s.find_last_not_of(" \t\r\n");return s.substr(a,b-a+1);}
std::string upper(std::string s){for(auto& c:s)c=static_cast<char>(std::toupper(static_cast<unsigned char>(c)));return s;}
unsigned valueOf(std::string s,const std::unordered_map<std::string,uint8_t>& symbols,int line){s=trim(s);auto it=symbols.find(upper(s));if(it!=symbols.end())return it->second;try{size_t n=0;int base=10;std::string v=s;if(v.size()>2&&v[0]=='0'&&(v[1]=='x'||v[1]=='X')){base=16;v=v.substr(2);}else if(!v.empty()&&v[0]=='$'){base=16;v=v.substr(1);}else if(!v.empty()&&v.back()=='h'){base=16;v.pop_back();}else if(v.find_first_of("ABCDEFabcdef")!=std::string::npos)base=16;unsigned long x=std::stoul(v,&n,base);if(n!=v.size()||x>255)throw std::runtime_error("");return static_cast<unsigned>(x);}catch(...){throw std::runtime_error("line "+std::to_string(line)+": invalid byte or unknown symbol '"+s+"'");}}
}
std::vector<Assembler::Line> Assembler::parse(const std::string& src)const{
 std::vector<Line> out;std::istringstream in(src);std::string raw;int no=0;unsigned pc=0;
 while(std::getline(in,raw)){++no;auto comment=raw.find(';');if(comment!=raw.npos)raw.resize(comment);raw=trim(raw);if(raw.empty())continue;std::string label,rest=raw;auto colon=rest.find(':');if(colon!=rest.npos){label=upper(trim(rest.substr(0,colon)));rest=trim(rest.substr(colon+1));}
 std::string op,arg;std::istringstream ss(rest);ss>>op;std::getline(ss,arg);op=upper(op);arg=trim(arg);if(op.empty()&&!label.empty()){out.push_back({no,static_cast<uint8_t>(pc),"", "",raw});continue;}unsigned size=0;if(op==".BYTE")size=1;else {auto it=InstructionSet.find(op);if(it==InstructionSet.end())throw std::runtime_error("line "+std::to_string(no)+": unknown instruction '"+op+"'");size=1+it->second.operandBytes;if((it->second.operandBytes==0&&!arg.empty())||(it->second.operandBytes==1&&arg.empty()))throw std::runtime_error("line "+std::to_string(no)+": wrong operand count for "+op);}
 if(pc+size>256)throw std::runtime_error("line "+std::to_string(no)+": program exceeds 256-byte address space");out.push_back({no,static_cast<uint8_t>(pc),op,arg,raw});pc+=size;
 }
 return out;
}
ObjectFile Assembler::assemble(const std::string& src){symbols_.clear();auto lines=parse(src);unsigned pc=0;for(const auto& l:lines){if(l.source.empty())continue;auto colon=l.source.find(':');if(colon!=l.source.npos){auto name=upper(trim(l.source.substr(0,colon)));if(name.empty())throw std::runtime_error("line "+std::to_string(l.number)+": empty label");if(symbols_.count(name))throw std::runtime_error("line "+std::to_string(l.number)+": duplicate label '"+name+"'");symbols_[name]=static_cast<uint8_t>(pc);}if(l.op==".BYTE"||InstructionSet.count(l.op))pc+=l.op==".BYTE"?1:1+InstructionSet.at(l.op).operandBytes;}
 ObjectFile obj;for(const auto& l:lines){if(l.source.empty())continue;if(l.op==".BYTE"){if(l.arg.empty())throw std::runtime_error("line "+std::to_string(l.number)+": .BYTE requires a value");obj.emit(static_cast<uint8_t>(valueOf(l.arg,symbols_,l.number)));continue;}if(l.op.empty())continue;const auto info=InstructionSet.at(l.op);obj.emit(static_cast<uint8_t>(info.opcode));if(info.operandBytes)obj.emit(static_cast<uint8_t>(valueOf(l.arg,symbols_,l.number)));}return obj;
}
std::string Assembler::listing(const std::string& src,const ObjectFile& obj)const{std::ostringstream o;auto lines=parse(src);size_t p=0;for(const auto& l:lines){if(l.op.empty())continue;o<<std::uppercase<<std::hex<<std::setw(2)<<std::setfill('0')<<unsigned(l.address)<<"  ";size_t n=l.op==".BYTE"?1:1+InstructionSet.at(l.op).operandBytes;for(size_t i=0;i<n&&p<obj.bytes().size();++i)o<<std::setw(2)<<unsigned(obj.bytes()[p++])<<' ';o<<" | "<<l.source<<'\n';}return o.str();}
