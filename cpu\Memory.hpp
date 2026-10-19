#pragma once
#include <array>
#include <cstdint>
class Memory{std::array<uint8_t,256> data_{};public:uint8_t read(uint8_t address)const;void write(uint8_t address,uint8_t value);void clear();};
