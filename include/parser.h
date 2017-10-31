#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <utility>
#include "atom.h"
#include "variable.h"
#include "number.h"
#include "scanner.h"
using std::string;
using std::pair;

class Parser{
public:
  Parser(Scanner scanner);
  Term* createTerm();
private:
  Scanner _scanner;
  Prolog* _prolog;
};
#endif
