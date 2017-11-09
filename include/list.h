#ifndef LIST_H
#define LIST_H

#include "struct.h"

class List : public Struct
{
public:
  List();
  List(Term *head, List *tail);
  List *getList();
  string domainSymbol();
  string domainValue();
  Term *head();
  List *tail();

private:
};

#endif