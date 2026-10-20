#include "Assembler.hpp"
#include "CPU.hpp"
#include <cstdlib>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

namespace {
int failures = 0;
void check(bool ok, const std::string& message) {
  if (!ok) { ++failures; std::cerr << "FAIL: " << message << '\n'; }
}
template<class F> void throws(F fn, const std::string& message) {
  try { fn(); check(false, message + " (did not throw)"); }
  catch (const std::exception&) { check(true, message); }
}
void assemblerExecution() {
  Assembler assembler;
  auto object = assembler.assemble(
    "LDI 3\n"
    "STA VALUE\n"
    "LDI 5\n"
    "STA ADDEND\n"
    "LDA VALUE\n"
    "ADD ADDEND\n"
    "OUT\n"
    "HLT\n"
    "VALUE: .BYTE 0\n"
    "ADDEND: .BYTE 0\n");
  CPU cpu; cpu.loadProgram(object.bytes()); cpu.run();
  check(cpu.outputsWritten().size() == 1 && cpu.outputsWritten()[0] == 8, "assembler and CPU compute 3 + 5");
  check(cpu.isHalted(), "HLT marks CPU halted");
}
void inputAndWraparound() {
  CPU cpu; cpu.queueInput(255); cpu.loadProgram({0x12,0x0C,0x09,0x0A}); cpu.run();
  check(cpu.outputsWritten().size() == 1 && cpu.outputsWritten()[0] == 0, "increment wraps 255 to zero");
  check(cpu.zeroFlag(), "zero flag is set on wraparound");
  check(cpu.inputsRemaining() == 0, "input FIFO is consumed");
}
void assemblerErrors() {
  Assembler a;
  throws([&]{a.assemble("BOGUS\n");}, "unknown instruction rejected");
  throws([&]{a.assemble("LDI 256\n");}, "out-of-range byte rejected");
  throws([&]{a.assemble("LDI MISSING\n");}, "unknown symbol rejected");
  throws([&]{a.assemble("HERE: NOP\nHERE: HLT\n");}, "duplicate label rejected");
  throws([&]{a.assemble(".BYTE\n");}, "missing .BYTE value rejected");
}
void boundsAndRunLimit() {
  CPU cpu;
  throws([&]{cpu.loadProgram(std::vector<uint8_t>(257,0));}, "program larger than memory rejected");
  cpu.reset(); cpu.loadProgram({0x06,0x00});
  throws([&]{cpu.run(20);}, "infinite loop triggers step limit");
}
}
int main() {
  assemblerExecution(); inputAndWraparound(); assemblerErrors(); boundsAndRunLimit();
  if (failures) { std::cerr << failures << " test(s) failed\n"; return EXIT_FAILURE; }
  std::cout << "All TTL8 tests passed\n"; return EXIT_SUCCESS;
}
