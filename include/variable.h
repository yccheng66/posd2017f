#ifndef VARIABLE_H
#define VARIABLE_H

#include "term.h"

class Variable : public Term
{
public:
  Variable(string symbol);
  string symbol();
  string value();
  bool match(Term *term);
  Variable *getVariable();

private:
  string getCorrectSymbol();
  bool matchInstance(Term *term);
  void instantiate(Term *term, Variable *variable);
  bool detectCycle(Variable *variable);
  bool isExistInInstances(Variable *variable);
  bool isExistInReferencers(Variable *variable);
  bool _isVisited;
  string _symbol;
  Term *_instance;       // The instance which is instantiated by variable //
  Variable *_referencer; // The variable which references(instantiates) this variable //
};

#endif