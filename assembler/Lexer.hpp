#pragma once
#include "Token.hpp"
#include <string>
#include <vector>
class Lexer {
public:
 std::vector<Token> tokenize(const std::string& source) const;
};
