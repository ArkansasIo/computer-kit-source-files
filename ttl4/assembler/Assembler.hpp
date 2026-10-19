#pragma once
#include "ObjectFile.hpp"
#include <string>
class Assembler{public:ObjectFile assemble(const std::string& source);};
