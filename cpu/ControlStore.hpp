#pragma once
#include <cstddef>
#include <cstdint>
#include <stdexcept>
#include <vector>
// Stores pre-encoded control words. Address layout must match the hardware
// definition supplied to microcode/generate_microcode.py.
class ControlStore {
 std::vector<uint32_t> words_;
 unsigned stepBits_=0;
public:
 void load(const std::vector<uint8_t>& bytes,unsigned wordBytes,unsigned stepBits){
  if(wordBytes<1||wordBytes>4||stepBits<1||stepBits>8||bytes.size()%(wordBytes)!=0)throw std::invalid_argument("invalid control-store image dimensions");
  words_.clear();words_.reserve(bytes.size()/wordBytes);stepBits_=stepBits;
  for(size_t i=0;i<bytes.size();i+=wordBytes){uint32_t word=0;for(unsigned j=0;j<wordBytes;++j)word|=uint32_t(bytes[i+j])<<(8*j);words_.push_back(word);}
 }
 uint32_t read(uint8_t opcode,uint8_t step)const{if(words_.empty())throw std::runtime_error("control store is empty");if(step>=(1u<<stepBits_))throw std::out_of_range("microstep outside control-store address range");size_t address=(size_t(opcode)<<stepBits_)|step;if(address>=words_.size())throw std::out_of_range("control-store address outside image");return words_[address];}
 size_t size()const{return words_.size();}
};
