#include "ObjectFile.hpp"
#include <cstddef>
#include <fstream>
#include <iomanip>
#include <stdexcept>
void ObjectFile::saveBinary(const std::string& filename)const{std::ofstream out(filename,std::ios::binary);if(!out)throw std::runtime_error("cannot write "+filename);out.write(reinterpret_cast<const char*>(bytes_.data()),static_cast<std::streamsize>(bytes_.size()));}
void ObjectFile::saveHex(const std::string& filename)const{std::ofstream out(filename);if(!out)throw std::runtime_error("cannot write "+filename);for(auto value:bytes_)out<<std::uppercase<<std::hex<<std::setw(2)<<std::setfill('0')<<unsigned(value)<<' ';out<<'\n';}
void ObjectFile::saveListing(const std::string& filename)const{std::ofstream out(filename);if(!out)throw std::runtime_error("cannot write "+filename);for(size_t i=0;i<bytes_.size();++i)out<<std::uppercase<<std::hex<<std::setw(2)<<std::setfill('0')<<i<<"  "<<std::setw(2)<<unsigned(bytes_[i])<<'\n';}
