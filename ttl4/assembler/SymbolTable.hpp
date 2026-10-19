#pragma once
#include <cstdint>
#include <string>
#include <unordered_map>
class SymbolTable {
 std::unordered_map<std::string,uint8_t> values_;
 static std::string canonical(const std::string& name);
public:
 void clear(){values_.clear();}
 bool contains(const std::string& name)const;
 void define(const std::string& name,uint8_t value);
 uint8_t resolve(const std::string& name)const;
};
