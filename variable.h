#ifndef VARIABLE_H
#define VARIABLE_H

#include <string>
#include "atom.h"
using std::string;

class Variable : public Term {
public:
  Variable(string s):Term(s), _instance(0) {

  }

  string value() const {
    if (_instance)
      return _instance->value();
    else
      return Term::value();
  }

  bool match( Term & term ) {
    if (_instance != nullptr)
      return _instance->match(term);
    if (&term != this)
      _instance = &term;
    return true;
  }

  Variable* getVariable() {
    return this;
  }
private:
  Term * _instance;
};

#endif
