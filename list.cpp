#include "atom.h"
#include "variable.h"
#include <typeinfo>
#include <iostream>
#include <string>
#include "list.h"
#include "iterator.h"
using std::vector;

Iterator * List::createIterator()
{
  return new ListIterator(this);
}

string List::symbol() const{
    string ret = "[";

    for (const List* current = this; current != nullptr; current = dynamic_cast<List*> (current->tail()))
    {
      ret += ((current != this ) ? ", " : "");
      ret += current->head()->symbol();
    }

    return ret + "]";
  }

string List::value() const{
  string ret = "[";

  for (const List* current = this; current != nullptr; current = dynamic_cast<List*> (current->tail()))
  {
    ret += ((current != this ) ? ", " : "");
    ret += current->head()->value();
  }

  return ret + "]";
}

Term * List::head() const{
    if(_args.empty())
        throw std::string("Accessing head in an empty list");

    return _args[0];
}

Term * List::tail() const {
    if(_args.empty())
        throw std::string("Accessing tail in an empty list");
    return _args[1];
}
