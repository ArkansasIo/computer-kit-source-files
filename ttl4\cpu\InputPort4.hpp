#pragma once
#include <cstddef>
#include <cstdint>
#include <deque>
#include <stdexcept>
class InputPort4{std::deque<uint8_t> values_;public:void write(uint8_t value);uint8_t read();size_t available()const;void clear();};
