#pragma once
#include <string>
enum class TokenType { Identifier, Number, Colon, Comma, Directive, EndOfLine };
struct Token { TokenType type; std::string text; int line=1; int column=1; };
