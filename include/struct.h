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
  Atom _functor;
  vector<Term *> _args;
};

#endif