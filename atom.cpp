#include "atom.h"
#include "variable.h"
#include "iterator.h"
//#include <typeinfo>

Iterator * Term::createIterator(){
  return new NullIterator(this);
}

bool Term::match(Term & a){
  if (a.getVariable() !=  nullptr)
    return a.match(*this);
  return symbol() == a.symbol();
}
