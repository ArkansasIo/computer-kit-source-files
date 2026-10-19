#include "Register.hpp"
void Register8::load(uint8_t value){value_=value;}
void Register8::clear(){value_=0;}
uint8_t Register8::read()const{return value_;}
