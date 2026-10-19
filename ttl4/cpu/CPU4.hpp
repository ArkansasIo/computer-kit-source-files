#pragma once
#include "Register4.hpp"
#include "ByteRegister.hpp"
#include "Bus4.hpp"
#include "ALU4.hpp"
#include "Memory4.hpp"
#include "ControlUnit4.hpp"
#include "InputPort4.hpp"
#include "OutputPort4.hpp"
#include <cstddef>
#include <cstdint>
#include <array>
#include <stdexcept>
#include <vector>
class CPU4{
 Register4 A,B;ByteRegister IR,MAR;uint8_t PC=0;bool carry=false,zero=false,halted=false;Bus4 bus;ALU4 alu;Memory4 memory;std::array<uint8_t,256> program{};InputPort4 input;OutputPort4 outputPort;
 uint8_t fetch();
 void setA(uint8_t value);
public:
 void reset();
 void queueInput(uint8_t value);
 void loadProgram(const std::vector<uint8_t>& program,uint8_t address=0);
 void step();
 void run(size_t limit=100000);
 uint8_t accumulator()const;
 uint8_t output()const;
 const std::vector<uint8_t>& outputsWritten()const;
 bool isHalted()const;
 bool carryFlag()const;
 bool zeroFlag()const;
 size_t inputsRemaining()const;
};
