#pragma once
#include <cstdint>
class Bus4{uint8_t value_=0;public:void write(uint8_t value);uint8_t read()const;};
