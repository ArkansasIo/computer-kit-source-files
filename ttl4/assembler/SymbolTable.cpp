#include "SymbolTable.hpp"
#include <algorithm>
#include <cctype>
#include <stdexcept>
std::string SymbolTable::canonical(const std::string& s){std::string r=s;std::transform(r.begin(),r.end(),r.begin(),[](unsigned char c){return char(std::toupper(c));});return r;}
bool SymbolTable::contains(const std::string& n)const{return values_.find(canonical(n))!=values_.end();}
void SymbolTable::define(const std::string& n,uint8_t v){if(n.empty())throw std::runtime_error("empty symbol name");auto key=canonical(n);if(values_.count(key))throw std::runtime_error("duplicate symbol '"+n+"'");values_[key]=v;}
uint8_t SymbolTable::resolve(const std::string& n)const{auto i=values_.find(canonical(n));if(i==values_.end())throw std::runtime_error("unknown symbol '"+n+"'");return i->second;}
