#include "atom.h"
#include "variable.h"
#include "iterator.h"
#include <typeinfo>

Iterator * Term::createIterator(){
  return new NullIterator(this);
}

bool Term::match(Term & a){
  if (typeid(a) ==  typeid(Variable))
    return a.match(*this);
  else
    return symbol() == a.symbol();
}
