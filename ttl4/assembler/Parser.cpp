#include "Parser.hpp"
#include <stdexcept>
std::vector<ParsedLine> Parser::parse(const std::vector<Token>& ts) const {
 std::vector<ParsedLine> result;size_t i=0;
 while(i<ts.size()){
  ParsedLine line;line.line=ts[i].line;
  while(i<ts.size()&&ts[i].type!=TokenType::EndOfLine){
   if(ts[i].type==TokenType::Colon){if(line.label.empty()||!line.operation.empty())throw std::runtime_error("line "+std::to_string(ts[i].line)+": misplaced ':'");++i;continue;}
   if(line.operation.empty()){
    if(i+1<ts.size()&&ts[i+1].type==TokenType::Colon){line.label=ts[i].text;i+=2;continue;}
    line.operation=ts[i++].text;
   }else if(line.operand.empty())line.operand=ts[i++].text;
   else throw std::runtime_error("line "+std::to_string(ts[i].line)+": too many operands");
   if(i<ts.size()&&ts[i].type==TokenType::Comma)++i;
  }
  if(!line.label.empty()||!line.operation.empty())result.push_back(line);
  if(i<ts.size())++i;
 }
 return result;
}
