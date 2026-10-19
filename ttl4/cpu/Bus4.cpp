#include "Bus4.hpp"
void Bus4::write(uint8_t value){value_=value&15;}
uint8_t Bus4::read()const{return value_;}
