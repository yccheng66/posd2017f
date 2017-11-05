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
  virtual string symbol();
  virtual string value();
  bool match(Term *term);
  Struct *getStruct();
  Atom functor();
  Term *args(int index);

protected:
  Struct(Atom functor, Term *head, Term *tail);
  Atom _functor;
  vector<Term *> _args;

private:
  string _delimiter;
  string _leftBrackets;
  string _rightBrackets;
};

#endif