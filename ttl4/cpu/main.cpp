#include "CPU4.hpp"
#include <fstream>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <stdexcept>
#include <string>
#include <vector>
static uint8_t parseInput(const std::string& s){int base=10;size_t start=0;if(s.size()>2&&s[0]=='0'&&(s[1]=='x'||s[1]=='X')){base=16;start=2;}else if(!s.empty()&&s[0]=='$'){base=16;start=1;}else if(s.find_first_of("abcdefABCDEF")!=std::string::npos)base=16;size_t used=0;unsigned long v=std::stoul(s.substr(start),&used,base);if(used!=s.size()-start||v>15)throw std::runtime_error("TTL4 input must be a nibble from 0 to F: "+s);return uint8_t(v);}
int main(int argc,char** argv){try{if(argc<2){std::cerr<<"usage: ttl4-run program.bin [input-nibble ...]\nValues accept decimal, 0x hex, $ hex, or bare hex containing A-F.\n";return 2;}std::ifstream f(argv[1],std::ios::binary);if(!f)throw std::runtime_error("cannot read binary");std::vector<uint8_t> bytes((std::istreambuf_iterator<char>(f)),{});CPU4 cpu;for(int i=2;i<argc;++i)cpu.queueInput(parseInput(argv[i]));cpu.loadProgram(bytes);cpu.run();for(auto v:cpu.outputsWritten())std::cout<<std::uppercase<<std::hex<<unsigned(v)<<'\n';}catch(const std::exception& e){std::cerr<<"ttl4-run: "<<e.what()<<'\n';return 1;}return 0;}
