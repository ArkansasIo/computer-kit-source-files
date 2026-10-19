#include "InputPort4.hpp"
void InputPort4::write(uint8_t value){values_.push_back(value&15);}
uint8_t InputPort4::read(){if(values_.empty())throw std::runtime_error("input port is empty; provide a value to ttl4-run");uint8_t value=values_.front();values_.pop_front();return value;}
size_t InputPort4::available()const{return values_.size();}
void InputPort4::clear(){values_.clear();}
