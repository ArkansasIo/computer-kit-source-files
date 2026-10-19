#include "Register4.hpp"
void Register4::load(uint8_t value){value_=value&15;}
void Register4::clear(){value_=0;}
uint8_t Register4::read()const{return value_;}
