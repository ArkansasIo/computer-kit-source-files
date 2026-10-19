#include "Assembler.hpp"
#include <fstream>
#include <iostream>
#include <iterator>
int main(int argc,char** argv){try{if(argc<2||argc>3){std::cerr<<"usage: ttl8-as source.asm [output-prefix]\n";return 2;}std::ifstream f(argv[1]);if(!f)throw std::runtime_error(std::string("cannot read ")+argv[1]);std::string src((std::istreambuf_iterator<char>(f)),{});Assembler a;auto obj=a.assemble(src);std::string prefix=argc==3?argv[2]:std::string(argv[1]);auto dot=prefix.find_last_of('.');if(argc==2&&dot!=std::string::npos)prefix.resize(dot);obj.saveBinary(prefix+".bin");obj.saveHex(prefix+".hex");std::ofstream lst(prefix+".lst");if(!lst)throw std::runtime_error("cannot write listing");lst<<a.listing(src,obj);std::cout<<"assembled "<<obj.bytes().size()<<" bytes\n";return 0;}catch(const std::exception& e){std::cerr<<"ttl8-as: "<<e.what()<<'\n';return 1;}}
