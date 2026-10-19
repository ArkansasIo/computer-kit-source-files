#pragma once
#include <cstdint>
// Manual two-phase clock model for future cycle-level simulation. CPU::step()
// currently executes one complete instruction and does not consume these edges.
class Clock {
 bool high_=false;
 uint64_t edges_=0;
public:
 bool high()const{return high_;}
 uint64_t edgeCount()const{return edges_;}
 void tick(){high_=!high_;++edges_;}
 void reset(){high_=false;edges_=0;}
};
