#include "../include/parser.h"

Parser::Parser(Scanner scanner) : _scanner(scanner), _prolog(Prolog::getInstance())
{}

Term* Parser::createTerm()
{
    pair<string, int> token = _scanner.nextToken();
    if(token.second == _prolog->VARIABLE)
        return new Variable(token.first);
    else if(token.second == _prolog->NUMBER)
        return new Number(stod(token.first));
}

/*Parser(Scanner scanner) : _scanner(scanner){}
Term* createTerm(){
  int token = _scanner.nextToken();
  if(token == VAR){
    return new Variable(symtable[_scanner.tokenValue()].first);
  }else if(token == NUMBER){
    return new Number(_scanner.tokenValue());
  }
  return NULL;
}*/