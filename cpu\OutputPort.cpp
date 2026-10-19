#include "OutputPort.hpp"
void OutputPort::write(uint8_t value){history_.push_back(value);}
uint8_t OutputPort::value()const{return history_.empty()?0:history_.back();}
const std::vector<uint8_t>& OutputPort::history()const{return history_;}
void OutputPort::clear(){history_.clear();}
