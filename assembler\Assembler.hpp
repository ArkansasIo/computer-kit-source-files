#pragma once
#include "Instruction.hpp"
#include "ObjectFile.hpp"
#include <string>
#include <unordered_map>
#include <vector>
class Assembler {
 std::unordered_map<std::string,uint8_t> symbols_;
 struct Line{int number;uint8_t address;std::string op,arg,source;};
 std::vector<Line> parse(const std::string&) const;
public:
 ObjectFile assemble(const std::string& source);
 std::string listing(const std::string& source,const ObjectFile& object) const;
};
