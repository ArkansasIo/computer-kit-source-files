#pragma once
#include "Token.hpp"
#include <string>
#include <vector>
struct ParsedLine { int line=1; std::string label,operation,operand; };
class Parser { public: std::vector<ParsedLine> parse(const std::vector<Token>& tokens) const; };
