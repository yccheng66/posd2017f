#ifndef UTLIST_H
#define UTLIST_H

#include "variable.h"
#include "list.h"

TEST(List, symbol){
  Atom emptylist("[]");
  Atom tom("tom");
  List list(&tom, & emptylist);
  ASSERT_EQ("tom", list.head()->symbol());
  ASSERT_EQ("[]", list.tail()->symbol());
  ASSERT_EQ("[tom]", list.symbol());
  ASSERT_EQ("[tom]", list.value());

}

TEST(List, vectorInit){
  vector<Term*> v = {new Atom("tom"), new Atom("jerry")};
  List list(v);
  ASSERT_EQ("[tom, jerry]", list.symbol());
}

TEST(List, match){
  vector<Term*> v = {new Atom("tom"), new Atom("jerry")};
  List list(v);
  List list2(v);
  ASSERT_TRUE(list.match(list2));
  Atom mary("mary");
  ASSERT_FALSE(list.match(mary));
  Variable X("X");
  Variable Y("Y");
  vector<Term*> v2 = {&X, &Y};
  List list3(v2);
  ASSERT_TRUE(list2.match(list3));
  ASSERT_EQ("[X, Y]", list3.symbol());
  ASSERT_EQ("[tom, jerry]", list3.value());
}
#endif
