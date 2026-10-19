#include "Memory.hpp"
uint8_t Memory::read(uint8_t address)const{return data_[address];}
void Memory::write(uint8_t address,uint8_t value){data_[address]=value;}
void Memory::clear(){data_.fill(0);}
