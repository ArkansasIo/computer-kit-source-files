#include "Bus.hpp"
void Bus::write(uint8_t data){value_=data;}
uint8_t Bus::read()const{return value_;}
