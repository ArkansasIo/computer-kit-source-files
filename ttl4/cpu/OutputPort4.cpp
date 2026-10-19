#include "OutputPort4.hpp"
void OutputPort4::write(uint8_t value){history_.push_back(value&15);}
uint8_t OutputPort4::value()const{return history_.empty()?0:history_.back();}
const std::vector<uint8_t>& OutputPort4::history()const{return history_;}
void OutputPort4::clear(){history_.clear();}
