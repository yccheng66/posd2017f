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
  else if (_currentToken.second == _prolog->ATOM || _currentToken.second == _prolog->ATOMSC)
  {
    Atom *atom = new Atom(_currentToken.first);
    if (_scanner.currentChar() == '(')
      return buildStruct(atom);
    return atom;
  }
  else if (_currentToken.second == '[')
    return buildListOrStruct();
  else
    return nullptr;
}

Term *Parser::buildStruct(Atom *functor)
{
  vector<Term *> args = getArgs();
  /* extract right parentheses */
  if (_scanner.nextToken().second == ')')
  {
    if (functor->symbol() == "." && args.size() == 2 && args[1]->match(&(_prolog->EMPTY_LIST)))
      return new List(args[0], args[1]);
    return new Struct(*functor, args);
  }
  throw string("unexpected token");
  /* Throw the syntax error when the current char is not right parentheses */
}

Term *Parser::buildListOrStruct()
{
  vector<Term *> args = getArgs();
  Term *tail = (args.size() == 0) ? nullptr : getTail();
  if (_currentToken.second == ']')
  {
    for (int i = args.size() - 1; i >= 0; i--)
    {
      if (tail->getList() || tail->match(&_prolog->EMPTY_LIST))
        tail = new List(args[i], tail);
      else
        tail = new Struct(Atom("."), {args[i], tail});
    }
    return (tail) ? tail : new List();
  }
  throw string("unexpected token");
}

vector<Term *> Parser::getArgs()
{
  vector<Term *> args;
  Term *term;
  /* Extract left parentheses */
  if (_scanner.currentChar() == '(')
    _scanner.nextToken();
  /* If current char is not right parentheses, then try to create term from next token. Check the 
     token is a comma or not when creating fail */
  while (_scanner.currentChar() != ')' && ((term = createTerm()) || _currentToken.second == ','))
    if (term)
      args.push_back(term);
  return args;
}

Term *Parser::getTail()
{
  Term *tail;
  if (_currentToken.second == '|')
  {
    tail = createTerm();
    _currentToken = _scanner.nextToken();
  }
  tail = &_prolog->EMPTY_LIST;
  return tail;
}