#include "../include/parser.h"
#include <iostream>

Parser::Parser(Scanner scanner) : _scanner(scanner), _utility(Utility::getInstance())
{
}

Term *Parser::createTerm()
{
  _currentToken = _scanner.nextToken();
  if (_currentToken.second == _utility->VARIABLE)
    return new Variable(_currentToken.first);
  else if (_currentToken.second == _utility->NUMBER)
    return new Number(stod(_currentToken.first));
  else if (_currentToken.second == _utility->ATOM || _currentToken.second == _utility->ATOMSC)
    return actualTermOfAtomToken();
  else if (_currentToken.second == '[')
    return buildStructByBrackets();
  else
    return nullptr;
}

Term *Parser::actualTermOfAtomToken()
{
  Atom *atom = new Atom(_currentToken.first);
  if (_scanner.currentChar() == '(')
    return buildStructByParentheses(atom);
  return atom;
}

Term *Parser::buildStructByParentheses(Atom *functor)
{
  const int HEAD = 0;
  const int TAIL = 1;
  _scanner.nextToken(); // extract left parentheses //
  vector<Term *> args = getArgs();
  if (_scanner.nextToken().second == ')')
  {
    // .(1, []) is a list, .(1, 2) is not a list //
    if (functor->symbol() == "." && args.size() == 2 && args[TAIL]->getList())
      return new List(args[HEAD], args[TAIL]->getList());
    return new Struct(*functor, args);
  }
  throw string("')' was missing when building a parentheses struct");
}

Term *Parser::buildStructByBrackets()
{
  vector<Term *> args = getArgs();
  Term *tail = getTailBeforeRightBrackets();
  if (_scanner.nextToken().second == ']')
  {
    for (int i = args.size() - 1; i >= 0; i--)
      tail = (tail->getList()) ? new List(args[i], tail->getList()) : new Struct(Atom("."), {args[i], tail});
    return tail;
  }
  throw string("']' was missing when building a brackets struct");
}

vector<Term *> Parser::getArgs()
{
  vector<Term *> args;
  Term *term;
  /* If the current char is not the end of struct, try to create term from next
   * token. Check if the token is comma when creating fail. */
  while (!isEndOfStruct() && ((term = createTerm()) || _currentToken.second == ','))
    if (term)
      args.push_back(term);
  return args;
}

bool Parser::isEndOfStruct()
{
  /* If you forget to extract space before next token, then the parser will 
   * throw exception in the following situations:
   * [      ], s(      ),  s(1      ), [1       ], etc.
   * because the current char is not a right parentheses or brackets, so it
   * will be extract by getArgs. */

  _scanner.skipLeadingWhiteSpace();
  return (_scanner.currentChar() == ')' || _scanner.currentChar() == ']');
}

Term *Parser::getTailBeforeRightBrackets()
{
  if (_currentToken.second == '|')
    return createTerm();
  return new List();
}