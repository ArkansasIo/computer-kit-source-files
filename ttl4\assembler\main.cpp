#include "Assembler.hpp"
#include <fstream>
#include <iostream>
#include <iterator>
#include <string>
int main(int argc,char** argv){try{if(argc<2||argc>3){std::cerr<<"usage: ttl4-as source.asm [output-prefix]\n";return 2;}std::ifstream f(argv[1]);if(!f)throw std::runtime_error("cannot open source");std::string src((std::istreambuf_iterator<char>(f)),{});Assembler a;auto obj=a.assemble(src);std::string p=argc==3?argv[2]:argv[1];if(argc==2){auto dot=p.find_last_of('.');if(dot!=p.npos)p.resize(dot);}obj.saveBinary(p+".bin");obj.saveHex(p+".hex");obj.saveListing(p+".lst");std::cout<<"assembled "<<obj.bytes().size()<<" bytes\n";}catch(const std::exception& e){std::cerr<<"ttl4-as: "<<e.what()<<'\n';return 1;}return 0;}
