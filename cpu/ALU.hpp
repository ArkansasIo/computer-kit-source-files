#pragma once
#include <cstdint>
struct ALUResult{uint8_t value;bool carry;bool zero;};
class ALU{public: ALUResult add(uint8_t a,uint8_t b)const; ALUResult subtract(uint8_t a,uint8_t b)const; uint8_t bitAnd(uint8_t a,uint8_t b)const; uint8_t bitOr(uint8_t a,uint8_t b)const; uint8_t bitXor(uint8_t a,uint8_t b)const; uint8_t bitNot(uint8_t a)const; };
