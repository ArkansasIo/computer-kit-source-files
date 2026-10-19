#include "ByteRegister.hpp"
void ByteRegister::load(uint8_t value){value_=value;}
void ByteRegister::clear(){value_=0;}
uint8_t ByteRegister::read()const{return value_;}
