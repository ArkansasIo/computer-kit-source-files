#include "ObjectFile.hpp"
#include <cstddef>
#include <cstddef>
#include <fstream>
#include <iomanip>
#include <stdexcept>
void ObjectFile::saveBinary(const std::string& filename)const{std::ofstream out(filename,std::ios::binary);if(!out)throw std::runtime_error("cannot write "+filename);out.write(reinterpret_cast<const char*>(code_.data()),static_cast<std::streamsize>(code_.size()));}
void ObjectFile::saveHex(const std::string& filename)const{std::ofstream out(filename);if(!out)throw std::runtime_error("cannot write "+filename);for(size_t i=0;i<code_.size();++i){if(i)out<<' ';out<<std::uppercase<<std::hex<<std::setw(2)<<std::setfill('0')<<unsigned(code_[i]);}out<<'\n';}
