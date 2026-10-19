#include "Memory4.hpp"
uint8_t Memory4::read(uint8_t address)const{return data_[address];}
void Memory4::write(uint8_t address,uint8_t value){data_[address]=value&15;}
void Memory4::clear(){data_.fill(0);}
