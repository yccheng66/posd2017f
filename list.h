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

public:

  List (vector<Term *> const & elements): Struct(Atom("."), {elements[0], createTail(elements)}){
  }

  List(Term * head, Term* tail):Struct(Atom("."), { head, tail }) {

  }

  Term * head() const;
  Term * tail() const;

  Term * args(int index) {
    return _elements[index];
  }

  int arity() const {
    return _elements.size();
  }

  Iterator * createIterator();
private:
  vector<Term *> _elements;
  
  Term* createTail(std::vector<Term*> const &args){
    Term* tail = new Atom("[]");
    for (int i = args.size() - 1; i > 0; i--) {
      tail = new List(args[i], tail);
    }
    return tail;
  }
};

#endif
