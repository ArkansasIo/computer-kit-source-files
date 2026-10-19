#include "Lexer.hpp"
#include <cctype>
#include <stdexcept>
std::vector<Token> Lexer::tokenize(const std::string& source) const {
 std::vector<Token> out;int line=1,col=1;size_t i=0;
 while(i<source.size()){
  char c=source[i];if(c=='\n'){out.push_back({TokenType::EndOfLine,"",line,col});++i;++line;col=1;continue;}
  if(c==' '||c=='\t'||c=='\r'){++i;++col;continue;}
  if(c==';'){while(i<source.size()&&source[i]!='\n'){++i;++col;}continue;}
  if(c==':'){out.push_back({TokenType::Colon,":",line,col});++i;++col;continue;}
  if(c==','){out.push_back({TokenType::Comma,",",line,col});++i;++col;continue;}
  int start=col;size_t begin=i;
  while(i<source.size()&&source[i]!=' '&&source[i]!='\t'&&source[i]!='\r'&&source[i]!='\n'&&source[i]!=':'&&source[i]!=','&&source[i]!=';'){++i;++col;}
  std::string word=source.substr(begin,i-begin);TokenType type=TokenType::Identifier;
  if(!word.empty()&&word[0]=='.')type=TokenType::Directive;
  else if(!word.empty()&&(std::isdigit(static_cast<unsigned char>(word[0]))||word[0]=='$'))type=TokenType::Number;
  out.push_back({type,word,line,start});
 }
 out.push_back({TokenType::EndOfLine,"",line,col});return out;
}
