#ifndef ATOM_H
#define ATOM_H

#include <string>

using std::string;


class Term{

public:
  virtual string symbol(){}

  virtual string value(){}

  virtual bool match(){}


};

class Atom : public Term{
public:
  Atom (string s):_symbol(s) {}
  bool operator ==(Atom a) {return _symbol == a._symbol;}
  string symbol() {
    return _symbol;
  }

  string _symbol;
};


#endif
