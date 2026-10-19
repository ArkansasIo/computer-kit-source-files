#pragma once
#include <cstdint>
// Wide register used for instruction bytes and memory addresses in the 4-bit CPU.
class ByteRegister{uint8_t value_=0;public:void load(uint8_t value);void clear();uint8_t read()const;};
