#pragma once
#include <cstdint>
#include <vector>
class OutputPort {
 std::vector<uint8_t> history_;
public:
 void write(uint8_t value);
 uint8_t value()const;
 const std::vector<uint8_t>& history()const;
 void clear();
};
