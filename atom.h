#ifndef ATOM_H
#define ATOM_H

#include <string>

using std::string;

class Atom {
public:
  Atom (string s):_symbol(s) {}
  bool operator ==(Atom a) {return _symbol == a._symbol;}
  string _symbol;
};

#endif
