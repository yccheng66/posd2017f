#ifndef TERM_H
#define TERM_H

#include <string>
using std::string;

class List;
class Struct;
class Variable;
class Term
{
public:
  virtual string symbol() = 0;
  virtual string value() = 0;
  virtual bool match(Term *term) = 0;
  virtual List *getList();
  virtual Struct *getStruct();
  virtual Variable *getVariable();

protected:
  //bool matchVariable(Variable *variable);

private:
};

#endif