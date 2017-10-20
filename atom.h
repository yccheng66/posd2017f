#ifndef ATOM_H
#define ATOM_H

#include <string>
#include <sstream>
using std::string;


class Term{
public:
  virtual string symbol() const {return _symbol;}
  virtual string value() const {return symbol();}
  virtual bool match(Term & a);
protected:
  Term ():_symbol(""){}
  Term (string s):_symbol(s) {}
  Term(double db){
    std::ostringstream strs;
    strs << db;
    _symbol = strs.str();
  }
  string _symbol;
};

class Atom : public Term{
public:
  Atom(string s):Term(s) {}
};

class Number : public Term{
public:
  Number(double db):Term(db) {}
};

#endif
