#include "../include/parser.h"
#include <iostream>

Parser::Parser(Scanner scanner) : _scanner(scanner), _prolog(Prolog::getInstance())
{
}

Term *Parser::createTerm()
{
  _currentToken = _scanner.nextToken();
  if (_currentToken.second == _prolog->VARIABLE)
    return new Variable(_currentToken.first);
  else if (_currentToken.second == _prolog->NUMBER)
    return new Number(stod(_currentToken.first));
  else if (_currentToken.second == _prolog->ATOM)
  {
    Atom *atom = new Atom(_currentToken.first);
    if ((_currentToken = _scanner.nextToken()).second == '(')
    {
      vector<Term *> args = getArgs();
      if (_currentToken.second == ')')
        return new Struct(*atom, args);
    }
    return atom;
  }
  else
    return nullptr;
}

vector<Term *> Parser::getArgs()
{
  vector<Term *> args;
  Term *term;
  while (((term = createTerm()) && _currentToken.second != ')') || _currentToken.second == ',')
    if (term)
      args.push_back(term);
  if (_currentToken.second == ')')
    args.push_back(term);
  return args;
}