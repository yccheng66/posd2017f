#ifndef STRUCT_H
#define STRUCT_H

#include "atom.h"
#include <vector>
#include <string>

using std::string;

class Struct: public Term {
public:
  Struct(Atom name, std::vector<Term *> args): _name(name), _args(args){
  }


  bool match(Term &term) {
    if (term.getVariable() != nullptr) {
      return term.match(*this);
    }
    Struct *s = term.getStruct();
    if (s == nullptr || s->arity() != arity() || !_name.match(s->_name))
      return false;

    for (int i = 0; i < _args.size(); i++)
      if (!s->_args[i]->match(*_args[i]))
        return false;
    return true;
  }

  Term * args(int index) {
    return _args[index];
  }

  Atom & name() {
    return _name;
  }

  string symbol() const {
      string ret = _name.symbol() + "(";
      for (int i = 0; i < _args.size(); i++)
        ret += ((i > 0) ?  ", "  : "") + _args[i]->symbol();
      return ret + ")";
  }

  string value() const {
    string ret = _name.symbol() + "(";
    for (int i = 0; i < _args.size(); i++)
      ret += ((i > 0) ?  ", "  : "") + _args[i]->value();
    return ret + ")";
  }

  int arity() const {
    return _args.size();
  }

  Struct* getStruct() {
    return this;
  }

  Iterator * createIterator();
protected:
  Atom _name;
  std::vector<Term *> _args;
};

#endif
