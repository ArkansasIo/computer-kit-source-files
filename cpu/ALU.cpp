#include "ALU.hpp"
ALUResult ALU::add(uint8_t a,uint8_t b)const{uint16_t r=uint16_t(a)+b;uint8_t v=uint8_t(r);return{v,r>255,v==0};}
ALUResult ALU::subtract(uint8_t a,uint8_t b)const{uint8_t v=uint8_t(a-b);return{v,a<b,v==0};}
uint8_t ALU::bitAnd(uint8_t a,uint8_t b)const{return a&b;}
uint8_t ALU::bitOr(uint8_t a,uint8_t b)const{return a|b;}
uint8_t ALU::bitXor(uint8_t a,uint8_t b)const{return a^b;}
uint8_t ALU::bitNot(uint8_t a)const{return uint8_t(~a);}
