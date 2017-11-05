#ifndef LIST_H
#define LIST_H

#include "struct.h"
using std::vector;

class List : public Struct
{
public:
  List(Term *head = nullptr, Term *tail = nullptr);
  string symbol();
  string value();
  string structSymbol();
  string structValue();
  List *getList();

private:
  const int _HEAD = 0;
  const int _TAIL = 1;
};

#endif