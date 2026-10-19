#include "CPU.hpp"
void CPU::reset(){A.clear();B.clear();IR.clear();MAR.clear();PC=0;carry=zero=halted=false;memory.clear();input.clear();outputPort.clear();}
void CPU::queueInput(uint8_t value){input.write(value);}
void CPU::loadProgram(const std::vector<uint8_t>& program,uint8_t address){if(program.size()>256u-address)throw std::runtime_error("program does not fit in memory");for(size_t i=0;i<program.size();++i)memory.write(static_cast<uint8_t>(address+i),program[i]);PC=address;halted=false;}
uint8_t CPU::fetch(){uint8_t value=memory.read(PC);++PC;return value;}
void CPU::setA(uint8_t value){A.load(value);zero=(value==0);}
void CPU::step(){if(halted)return;IR.load(fetch());uint8_t op=IR.read(),arg=0;switch(op){case 0x00:break;case 0x01:arg=fetch();setA(memory.read(arg));break;case 0x02:arg=fetch();B.load(memory.read(arg));break;case 0x03:arg=fetch();{auto r=alu.add(A.read(),memory.read(arg));setA(r.value);carry=r.carry;}break;case 0x04:arg=fetch();{auto r=alu.subtract(A.read(),memory.read(arg));setA(r.value);carry=r.carry;}break;case 0x05:arg=fetch();memory.write(arg,A.read());break;case 0x06:PC=fetch();break;case 0x07:arg=fetch();if(zero)PC=arg;break;case 0x08:arg=fetch();if(carry)PC=arg;break;case 0x09:outputPort.write(A.read());break;case 0x0A:halted=true;break;case 0x0B:setA(fetch());break;case 0x0C:setA(uint8_t(A.read()+1));break;case 0x0D:setA(uint8_t(A.read()-1));break;case 0x0E:arg=fetch();setA(alu.bitAnd(A.read(),memory.read(arg)));break;case 0x0F:arg=fetch();setA(alu.bitOr(A.read(),memory.read(arg)));break;case 0x10:arg=fetch();setA(alu.bitXor(A.read(),memory.read(arg)));break;case 0x11:setA(alu.bitNot(A.read()));break;case 0x12:setA(input.read());break;default:halted=true;throw std::runtime_error("invalid opcode at address "+std::to_string(uint8_t(PC-1)));}}
void CPU::run(size_t maxSteps){for(size_t i=0;i<maxSteps&&!halted;++i)step();if(!halted)throw std::runtime_error("execution step limit reached");}
uint8_t CPU::accumulator()const{return A.read();}
uint8_t CPU::output()const{return outputPort.value();}
const std::vector<uint8_t>& CPU::outputsWritten()const{return outputPort.history();}
uint8_t CPU::programCounter()const{return PC;}
bool CPU::isHalted()const{return halted;}
bool CPU::carryFlag()const{return carry;}
bool CPU::zeroFlag()const{return zero;}
size_t CPU::inputsRemaining()const{return input.available();}
