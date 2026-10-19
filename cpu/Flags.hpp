#pragma once
#include <cstdint>
struct Flags {
 bool carry=false;
 bool zero=false;
 void clear(){carry=false;zero=false;}
 void updateZero(uint8_t value){zero=(value==0);}
};
