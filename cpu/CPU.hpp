#pragma once
#include "Register.hpp"
#include "Bus.hpp"
#include "ALU.hpp"
#include "Memory.hpp"
#include "InputPort.hpp"
#include "OutputPort.hpp"
#include <cstddef>
#include <cstdint>
#include <stdexcept>
#include <vector>
class CPU {
 Register8 A,B,IR,MAR;uint8_t PC=0;bool carry=false,zero=false,halted=false;Bus bus;ALU alu;Memory memory;InputPort input;OutputPort outputPort;
 uint8_t fetch();
 void setA(uint8_t value);
public:
 void reset();
 void queueInput(uint8_t value);
 void loadProgram(const std::vector<uint8_t>& program,uint8_t address=0);
 void step();
 void run(size_t maxSteps=1000000);
 uint8_t accumulator()const;
 uint8_t output()const;
 const std::vector<uint8_t>& outputsWritten()const;
 uint8_t programCounter()const;
 bool isHalted()const;
 bool carryFlag()const;
 bool zeroFlag()const;
 size_t inputsRemaining()const;
};
