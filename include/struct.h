#ifndef STRUCT_H
#define STRUCT_H

#include <vector>
#include "term.h"
#include "atom.h"
#include "variable.h"
using std::vector;

class Struct : public Term
{
public:
  Struct(Atom functor, vector<Term *> args);
  string symbol();
  string value();
  bool match(Term *term);
  Struct *getStruct();
  Atom functor();
  Term *args(int index);
  int arity();
  bool isSpecialStruct();

protected:
  Atom _functor;
  vector<Term *> _args;
  string openParenthesesOutput(bool isSymbol, bool isDomain = false);
  string openBracketsOutput(bool isSymbol);
  string argOutput(int index, bool isSymbol, bool isDomain = false);

private:
};

#endif