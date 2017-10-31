#ifndef LIST_H
#define LIST_H

#include "struct.h"
using std::vector;

class List : public Struct
{
public:
  List(vector<Term *> args);
  string symbol();
  string value();
  List *getList();
  /*List(vector<Term *> args, bool isConcat);
  string symbol();
  string value();
  bool match(Term *term);
  List *getList();
  Term *args(int index);*/

private:
  /*bool preprocess(List concat, List other);
  bool matchList(List *list, List *other);
  bool _isConcat;
  vector<Term *> _args;*/
};

#endif