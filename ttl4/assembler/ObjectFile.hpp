#pragma once
#include <cstdint>
#include <string>
#include <vector>
class ObjectFile{std::vector<uint8_t> bytes_;public:void emit(uint8_t value){bytes_.push_back(value);}const std::vector<uint8_t>& bytes()const{return bytes_;}void saveBinary(const std::string& filename)const;void saveHex(const std::string& filename)const;void saveListing(const std::string& filename)const;};
