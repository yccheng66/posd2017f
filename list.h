#ifndef LIST_H
#define LIST_H

#include "struct.h"
#include <vector>
#include <typeinfo>
#include <iostream>
using std::vector;
class Variable ;

class List : public Struct {
public:
  string symbol() const ;
  string value() const ;
  bool match(Term & term) ;
public:
  List (): _elements(0) {}
  List (vector<Term *> const & elements):_elements(elements){}

  List(Term * head, Term* tail):Struct(Atom("."), { head, tail }) {
    
  }

  List (vector<Term *> &elements) {
    Term* tail = new Atom("[]");
    for (int i = elements.size() - 1; i >= 0; i--) {
      tail = new List(elements[i], tail);
    }
  }

  Term * head() const;
  List * tail() const;
  Term * args(int index) {
    return _elements[index];
  }
  int arity() const {return _elements.size();}
  Iterator * createIterator();
private:
  vector<Term *> _elements;
};

#endif
