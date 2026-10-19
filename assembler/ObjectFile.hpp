#pragma once
#include <cstdint>
#include <string>
#include <vector>
class ObjectFile {
 std::vector<uint8_t> code_;
public:
 void emit(uint8_t b){code_.push_back(b);} const std::vector<uint8_t>& bytes()const{return code_;}
 void saveBinary(const std::string& filename)const;
 void saveHex(const std::string& filename)const;
};
