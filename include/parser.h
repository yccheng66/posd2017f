#ifndef PARSER_H
#define PARSER_H

#include "number.h"
#include "list.h"
#include "scanner.h"
using std::string;
using std::pair;

class Parser
{
public:
  Parser(Scanner scanner);
  Term *createTerm();
  Term *actualTermOfAtomToken();
  Term *buildStructByParentheses(Atom *functor);
  Term *buildStructByBrackets();
  vector<Term *> getArgs();

private:
  bool isEndOfStruct();
  Term *getTailBeforeRightBrackets();
  Scanner _scanner;
  Utility *_utility;
  pair<string, int> _currentToken;
};
#endif
