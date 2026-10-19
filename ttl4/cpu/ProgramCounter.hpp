#pragma once
#include <cstdint>
// The TTL8 program counter is an 8-bit address and wraps at 0xFF.
class ProgramCounter {
 uint8_t value_=0;
public:
 void reset(){value_=0;}
 uint8_t read()const{return value_;}
 void load(uint8_t value){value_=value;}
 void increment(){value_=static_cast<uint8_t>(value_+1);}
};
