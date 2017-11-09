#ifndef UTVARIABLE_H
#define UTVARIABLE_H

#include "../include/atom.h"
#include "../include/number.h"
#include "../include/variable.h"
#include "../include/struct.h"
#include "../include/list.h"

// symbol of variable //
TEST(variable, symbol)
{
  Variable X("X");
  EXPECT_EQ("X", X.symbol());
}

// value of variable before matching //
TEST(variable, valueWithoutInstance)
{
  Variable X("X");
  EXPECT_EQ("X", X.value());
}

// value of variable after matching //
TEST(variable, valueWithInstance)
{
  Atom tom("tom");
  Variable X("X");
  X.match(&tom);
  EXPECT_EQ("tom", X.value());
}

// -? X = tom. //
// X = tom. //
TEST(variable, matchAtom)
{
  Variable X("X");
  Atom tom("tom");
  EXPECT_TRUE(X.match(&tom));
  EXPECT_EQ("tom", X.value());
}

// -? X = 1. //
// X = 1. //
TEST(variable, matchNumber)
{
  Variable X("X");
  Number n(1);
  EXPECT_TRUE(X.match(&n));
  EXPECT_EQ("1", X.value());
}

// -? X = s(). //
// X = s(). //
TEST(variable, matchStruct)
{
  Variable X("X");
  Struct s(Atom("s"), {});
  EXPECT_TRUE(X.match(&s));
  EXPECT_EQ("s()", X.value());
}

// -? X = []. //
// X = []. //
TEST(variable, matchList)
{
  Variable X("X");
  List e;
  EXPECT_TRUE(X.match(&e));
  EXPECT_EQ("[]", X.value());
}

// -? X = Y. //
// X = Y. //
TEST(variable, matchVariable)
{
  Variable X("X");
  Variable Y("Y");
  EXPECT_TRUE(X.match(&Y));
  EXPECT_EQ("Y", X.value());
}

// -? X = X. //
// true. //
TEST(variable, avoidCycle)
{
  Variable X("X");
  EXPECT_TRUE(X.match(&X));
  EXPECT_EQ("X", X.value());
}

// -? X = Y, Y = X. //
// X = Y. //
TEST(variable, avoidCycle2)
{
  Variable X("X");
  Variable Y("Y");
  EXPECT_TRUE(X.match(&Y));
  EXPECT_TRUE(Y.match(&X));
  EXPECT_EQ("Y", X.value());
  EXPECT_EQ("Y", Y.value());
}

// -? X = Y, X = X. //
// X = Y. //
TEST(variable, avoidCycle3)
{
  Variable X("X");
  Variable Y("Y");
  EXPECT_TRUE(X.match(&Y));
  EXPECT_TRUE(X.match(&X));
  EXPECT_EQ("Y", X.value());
  EXPECT_EQ("Y", Y.value());
}

// -? X = Y, Y = Z, Z = W, Y = W. //
// X = Y, Y = Z, Z = w. //
TEST(variable, avoidCycle4)
{
  Variable W("W");
  Variable X("X");
  Variable Y("Y");
  Variable Z("Z");
  EXPECT_TRUE(X.match(&Y));
  EXPECT_TRUE(Y.match(&Z));
  EXPECT_TRUE(Z.match(&W));
  EXPECT_TRUE(Y.match(&W));
  EXPECT_EQ("W", X.value());
  EXPECT_EQ("W", Y.value());
  EXPECT_EQ("W", Z.value());
  EXPECT_EQ("W", W.value());
}

// -? X = s(X). //
// X = s(X). //
TEST(variable, avoidCycleValue)
{
  Variable X("X");
  Struct s(Atom("s"), {&X});
  EXPECT_TRUE(X.match(&s));
  EXPECT_EQ("s(X)", X.value());
}

// -? X = [X]. //
// X = [X]. //
TEST(variable, avoidCycleValue2)
{
  Variable X("X");
  List e;
  List l(&X, &e);
  EXPECT_TRUE(X.match(&l));
  EXPECT_EQ("[X]", X.value());
}

// -? X = s(X, s(X)). //
// X = s(X, s(X)). //
TEST(variable, avoidCycleValue3)
{
  Variable X("X");
  Struct s0(Atom("s"), {&X});
  Struct s1(Atom("s"), {&X, &s0});
  EXPECT_TRUE(X.match(&s1));
  EXPECT_EQ("s(X, s(X))", X.value());
}

// -? X = [X, [X]]. //
// X = [X, [X]]. //
TEST(variable, avoidCycleValue4)
{
  Variable X("X");
  List e;
  List l0(&X, &e);
  List l1(&l0, &e);
  List l2(&X, &l1);
  EXPECT_TRUE(X.match(&l2));
  EXPECT_EQ("[X, [X]]", X.value());
}

// -? X = Y, Y = Z, Z = 1. //
// X = Y, Y = Z, Z = 1. //
TEST(variable, matchInstance)
{
  Variable X("X");
  Variable Y("Y");
  Variable Z("Z");
  Number n(1);
  EXPECT_TRUE(X.match(&Y));
  EXPECT_TRUE(Y.match(&Z));
  EXPECT_TRUE(Z.match(&n));
  EXPECT_EQ("1", X.value());
  EXPECT_EQ("1", Y.value());
  EXPECT_EQ("1", Z.value());
}

// -? X = s(X), X = Y. //
// X = Y, Y = s(Y). //
// This is a bug when matching the variable with a struct instance //
// and the arg contain itself. //
TEST(variable, bugOfSymbol)
{
  Variable X("X");
  Struct s(Atom("s"), {&X});
  X.match(&s);
  Variable Y("Y");
  X.match(&Y);
  //EXPECT_EQ("s(Y)", X.value());
  //EXPECT_EQ("s(Y)", Y.value());
}

#endif
