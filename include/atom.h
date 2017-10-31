#ifndef ATOM_H
#define ATOM_H

#include "term.h"
#include "variable.h"

class Atom : public Term
{
public:
  Atom(string symbol);
  string symbol();
  string value();
  bool match(Term *term);

private:
  string _symbol;
};

#endif