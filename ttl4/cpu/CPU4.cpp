#include "CPU4.hpp"
void CPU4::reset(){A.clear();B.clear();IR.clear();MAR.clear();PC=0;carry=zero=halted=false;memory.clear();program.fill(0);input.clear();outputPort.clear();}
void CPU4::queueInput(uint8_t value){input.write(value);}
void CPU4::loadProgram(const std::vector<uint8_t>& bytes,uint8_t address){if(bytes.size()>256u-address)throw std::runtime_error("program does not fit 256-byte ROM");program.fill(0);for(size_t i=0;i<bytes.size();++i)program[uint8_t(address+i)]=bytes[i];PC=address;halted=false;}
uint8_t CPU4::fetch(){uint8_t value=program[PC];PC=uint8_t(PC+1);return value;}
void CPU4::setA(uint8_t value){A.load(value);zero=(A.read()==0);}
void CPU4::step(){if(halted)return;uint8_t op=fetch(),arg=0;IR.load(op);if(!ControlUnit4::validOpcode(op))throw std::runtime_error("invalid opcode");switch(op){case 0x00:break;case 0x01:arg=fetch();setA(memory.read(arg));break;case 0x02:arg=fetch();B.load(memory.read(arg));break;case 0x03:arg=fetch();{auto r=alu.add(A.read(),memory.read(arg));setA(r.value);carry=r.carry;}break;case 0x04:arg=fetch();{auto r=alu.subtract(A.read(),memory.read(arg));setA(r.value);carry=r.carry;}break;case 0x05:arg=fetch();memory.write(arg,A.read());break;case 0x06:PC=fetch();break;case 0x07:arg=fetch();if(zero)PC=arg;break;case 0x08:arg=fetch();if(carry)PC=arg;break;case 0x09:outputPort.write(A.read());break;case 0x0A:halted=true;break;case 0x0B:setA(fetch());break;case 0x0C:setA(A.read()+1);break;case 0x0D:setA(A.read()-1);break;case 0x0E:arg=fetch();setA(alu.bitAnd(A.read(),memory.read(arg)));break;case 0x0F:arg=fetch();setA(alu.bitOr(A.read(),memory.read(arg)));break;case 0x10:arg=fetch();setA(alu.bitXor(A.read(),memory.read(arg)));break;case 0x11:setA(alu.bitNot(A.read()));break;case 0x12:setA(input.read());break;default:throw std::runtime_error("invalid opcode");}}
void CPU4::run(size_t limit){for(size_t i=0;i<limit&&!halted;++i)step();if(!halted)throw std::runtime_error("instruction limit reached");}
uint8_t CPU4::accumulator()const{return A.read();}
uint8_t CPU4::output()const{return outputPort.value();}
const std::vector<uint8_t>& CPU4::outputsWritten()const{return outputPort.history();}
bool CPU4::isHalted()const{return halted;}
bool CPU4::carryFlag()const{return carry;}
bool CPU4::zeroFlag()const{return zero;}
size_t CPU4::inputsRemaining()const{return input.available();}
