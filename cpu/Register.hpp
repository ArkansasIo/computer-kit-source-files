#pragma once
#include <cstdint>
class Register8 { uint8_t value_=0; public: void load(uint8_t value); void clear(); uint8_t read()const; };
