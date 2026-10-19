#include "InputPort.hpp"
void InputPort::write(uint8_t value){values_.push_back(value);}
uint8_t InputPort::read(){if(values_.empty())throw std::runtime_error("input port is empty; provide a value to ttl8-run");uint8_t value=values_.front();values_.pop_front();return value;}
size_t InputPort::available()const{return values_.size();}
void InputPort::clear(){values_.clear();}
