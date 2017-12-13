#ifndef ATOM_H
#define ATOM_H

#include <string>
#include <sstream>
using std::string;

class Variable;
class Struct;
class Iterator;
class Term {
public:
  virtual string symbol() const {return _symbol;}
  virtual string value() const {return symbol();}
  virtual bool match(Term & a);
  virtual Iterator * createIterator();
  virtual Struct* getStruct() {
    return nullptr;
  }
  virtual Variable* getVariable() {
    return nullptr;
  }
protected:
  Term (string s = ""):_symbol(s) {}
  string _symbol;
};

class Atom : public Term{
public:
  Atom(string s):Term(s) {}
};

class Number : public Term{
public:
  Number(double db){
      std::ostringstream strs;
      strs << db;
      _symbol = strs.str();
  }
};

#endif
