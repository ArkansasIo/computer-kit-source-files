#pragma once
#include <cstdint>
#include <cstddef>
#include <deque>
#include <stdexcept>
class InputPort {
 std::deque<uint8_t> values_;
public:
 void write(uint8_t value);
 uint8_t read();
 size_t available()const;
 void clear();
};
