#pragma once
#include <cstdint>
class Bus { uint8_t value_=0; public: void write(uint8_t data); uint8_t read()const; };
