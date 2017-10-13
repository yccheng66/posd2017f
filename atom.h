#ifndef ATOM_H
#define ATOM_H

#include <string>

using std::string;


class Term{

public:
  virtual string symbol() const= 0;

  virtual string value() const{
    return symbol();
  };

  virtual bool match(Term & term) {
    return symbol() == term.symbol();
  }


};

class Atom : public Term{
public:
  Atom (string s):_symbol(s) {}

  string symbol() const{
    return _symbol;
  }

  string _symbol;
};


#endif
