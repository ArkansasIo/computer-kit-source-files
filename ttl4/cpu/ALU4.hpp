#pragma once
#include <cstdint>
struct ALU4Result{uint8_t value;bool carry;bool zero;};
class ALU4{public:ALU4Result add(uint8_t a,uint8_t b)const;ALU4Result subtract(uint8_t a,uint8_t b)const;uint8_t bitAnd(uint8_t a,uint8_t b)const;uint8_t bitOr(uint8_t a,uint8_t b)const;uint8_t bitXor(uint8_t a,uint8_t b)const;uint8_t bitNot(uint8_t a)const;};
