#include "CPU.hpp"
#include <fstream>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <cctype>
#include <stdexcept>
#include <string>
#include <vector>
static uint8_t parseInput(const std::string& s){int base=10;size_t start=0;if(s.size()>2&&s[0]=='0'&&(s[1]=='x'||s[1]=='X')){base=16;start=2;}else if(!s.empty()&&s[0]=='$'){base=16;start=1;}else if(s.find_first_of("abcdefABCDEF")!=std::string::npos)base=16;size_t used=0;unsigned long v=std::stoul(s.substr(start),&used,base);if(used!=s.size()-start||v>255)throw std::runtime_error("input must be a byte (decimal or hex): "+s);return uint8_t(v);}
int main(int argc,char** argv){try{if(argc<2){std::cerr<<"usage: ttl8-run program.bin [input-value ...]\nValues accept decimal, 0x hex, $ hex, or bare hex containing A-F.\n";return 2;}std::ifstream in(argv[1],std::ios::binary);if(!in)throw std::runtime_error(std::string("cannot read ")+argv[1]);std::vector<uint8_t> bytes((std::istreambuf_iterator<char>(in)),{});CPU cpu;for(int i=2;i<argc;++i)cpu.queueInput(parseInput(argv[i]));cpu.loadProgram(bytes);cpu.run();for(uint8_t v:cpu.outputsWritten())std::cout<<std::uppercase<<std::hex<<std::setw(2)<<std::setfill('0')<<unsigned(v)<<'\n';return 0;}catch(const std::exception& e){std::cerr<<"ttl8-run: "<<e.what()<<'\n';return 1;}}
