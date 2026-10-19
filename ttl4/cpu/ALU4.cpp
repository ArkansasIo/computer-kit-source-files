#include "ALU4.hpp"
ALU4Result ALU4::add(uint8_t a,uint8_t b)const{unsigned r=(a&15)+(b&15);uint8_t v=uint8_t(r&15);return{v,r>15,v==0};}
ALU4Result ALU4::subtract(uint8_t a,uint8_t b)const{a&=15;b&=15;uint8_t v=uint8_t((a-b)&15);return{v,a<b,v==0};}
uint8_t ALU4::bitAnd(uint8_t a,uint8_t b)const{return(a&b)&15;}
uint8_t ALU4::bitOr(uint8_t a,uint8_t b)const{return(a|b)&15;}
uint8_t ALU4::bitXor(uint8_t a,uint8_t b)const{return(a^b)&15;}
uint8_t ALU4::bitNot(uint8_t a)const{return uint8_t((~a)&15);}
