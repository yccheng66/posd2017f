#ifndef UTSTRUCT_H
#define UTSTRUCT_H

#include "../include/atom.h"
#include "../include/number.h"
#include "../include/variable.h"
#include "../include/struct.h"

// Test the functor and args of struct //
TEST(structure, constructor)
{
    Struct s(Atom("s"), {});
    EXPECT_EQ("s", s.functor().symbol());
    EXPECT_FALSE(s.args(0));
}

// functor(args) = s()
TEST(structure, symbolWithoutArgs)
{
    Struct s(Atom("s"), {});
    EXPECT_EQ("s()", s.symbol());
}

// functor(args) = s(tom, jerry)
TEST(structure, symbolWithAtomArgs)
{
    Atom tom("tom");
    Atom jerry("jerry");
    Struct s(Atom("s"), {&tom, &jerry});
    EXPECT_EQ("s(tom, jerry)", s.symbol());
}

// functor(args) = s(1, -1)
TEST(structure, symbolWithNumberArgs)
{
    Number n1(1);
    Number n2(-1);
    Struct s(Atom("s"), {&n1, &n2});
    EXPECT_EQ("s(1, -1)", s.symbol());
}

// functor(args) = s(X, Y)
TEST(structure, symbolWithVariableArgs)
{
    Variable X("X");
    Variable Y("Y");
    Struct s(Atom("s"), {&X, &Y});
    EXPECT_EQ("s(X, Y)", s.symbol());
}

// functor(args) = s(tom, 1, X)
TEST(structure, symbol)
{
    Atom tom("tom");
    Number n1(1);
    Variable X("X");
    Struct s(Atom("s"), {&tom, &n1, &X});
    EXPECT_EQ("s(tom, 1, X)", s.symbol());
}

// functor(args) = s(tom, sub(tom))
TEST(structure, symbolWithStructArgs)
{
    Atom tom("tom");
    Struct sub(Atom("sub"), {&tom});
    Struct s(Atom("s"), {&tom, &sub});
    EXPECT_EQ("s(tom, sub(tom))", s.symbol());
}

// functor(args) = s()
TEST(structure, valueWithoutArgs)
{
    Struct s(Atom("s"), {});
    EXPECT_EQ("s()", s.value());
}

// functor(args) = s(tom, jerry)
TEST(structure, valueWithAtomArgs)
{
    Atom tom("tom");
    Atom jerry("jerry");
    Struct s(Atom("s"), {&tom, &jerry});
    EXPECT_EQ("s(tom, jerry)", s.value());
}

// functor(args) = s(1, -1)
TEST(structure, valueWithNumberArgs)
{
    Number n1(1);
    Number n2(-1);
    Struct s(Atom("s"), {&n1, &n2});
    EXPECT_EQ("s(1, -1)", s.value());
}

// functor(args) = s(X, Y)
TEST(structure, valueWithVariableArgs)
{
    Variable X("X");
    Variable Y("Y");
    Struct s(Atom("s"), {&X, &Y});
    EXPECT_EQ("s(X, Y)", s.value());
}

// functor(args) = s(tom, 1, X)
TEST(structure, value)
{
    Atom tom("tom");
    Number n1(1);
    Variable X("X");
    Struct s(Atom("s"), {&tom, &n1, &X});
    EXPECT_EQ("s(tom, 1, X)", s.value());
}

// -? s(tom) = tom.
// false.
// -? s2(1) = 1.
// false.
TEST(structure, matchNonStruct)
{
    Atom tom("tom");
    Number n1(1);
    Struct s(Atom("s"), {&tom});
    EXPECT_FALSE(s.match(&tom));
    Struct s2(Atom("s2"), {&n1});
    EXPECT_FALSE(s2.match(&n1));
}

// -? s(X) = X.
// X = s(X).
TEST(structure, matchVariable)
{
    Variable X("X");
    Struct s(Atom("s"), {&X});
    EXPECT_TRUE(s.match(&X));
    EXPECT_TRUE(s.match(&X));
    EXPECT_EQ("s(X)", X.value());
}

// -? s() = s2().
// false.
TEST(structure, matchStructWithDifferentFunctor)
{
    Struct s(Atom("s"), {});
    Struct s2(Atom("s2"), {});
    EXPECT_FALSE(s.match(&s2));
}

// -? s(tom) = s().
// false.
TEST(structure, matchStructWithDifferentArgSize)
{
    Atom tom("tom");
    Struct s(Atom("s"), {&tom});
    Struct s2(Atom("s"), {});
    EXPECT_FALSE(s.match(&s2));
}

// -? s(tom) = s(jerry).
// false.
TEST(structure, matchStructWithDifferentArgs)
{
    Atom tom("tom");
    Atom jerry("jerry");
    Struct s(Atom("s"), {&tom});
    Struct s2(Atom("s"), {&jerry});
    EXPECT_FALSE(s.match(&s2));
}

// -? s(tom, 1, X) = s(tom, 1, X).
// true.
TEST(structure, matchStructWithCorrespondingArgs)
{
    Atom tom("tom");
    Number n1(1);
    Variable X("X");
    Struct s(Atom("s"), {&tom, &n1, &X});
    Struct s2(Atom("s"), {&tom, &n1, &X});
    EXPECT_TRUE(s.match(&s2));
}

// -? s(tom, 1, X) = s(tom, X, 1).
// X = 1.
TEST(structure, match)
{
    Atom tom("tom");
    Number n1(1);
    Variable X("X");
    Struct s(Atom("s"), {&tom, &n1, &X});
    Struct s2(Atom("s"), {&tom, &X, &n1});
    EXPECT_TRUE(s.match(&s2));
    EXPECT_EQ("1", X.value());
}

// -? s(tom, 1, X) = s(X, 1, 1).
// false.
TEST(structure, match2)
{
    Atom tom("tom");
    Number n1(1);
    Variable X("X");
    Struct s(Atom("s"), {&tom, &n1, &X});
    Struct s2(Atom("s"), {&X, &n1, &n1});
    EXPECT_FALSE(s.match(&s2));
    EXPECT_EQ("tom", X.value());
}

// -? X = s(tom, X).
// X = s(tom, X).
TEST(structure, cycleValue)
{
    Atom tom("tom");
    Variable X("X");
    Struct s(Atom("s"), {&tom, &X});
    X.match(&s);
    EXPECT_EQ("s(tom, X)", X.value());
}

// -? X = Y, Y = Z, Z = X, Y = s(Y).
// X = Y, Y = Z, Z = s(Z).
TEST(structure, cycleValue2)
{
    Variable X("X");
    Variable Y("Y");
    Variable Z("Z");
    Struct s(Atom("s"), {&Y});
    X.match(&Y);
    Y.match(&Z);
    Z.match(&X);
    EXPECT_TRUE(Y.match(&s));
    EXPECT_EQ("s(Z)", X.value());
    EXPECT_EQ("s(Z)", Y.value());
    EXPECT_EQ("s(Z)", Z.value());
}

// -? X = Y, Y = Z, Y = X, Y = 1, Y = s(Y).
// false
TEST(structure, cycleValue3)
{
    Variable X("X");
    Variable Y("Y");
    Variable Z("Z");
    Number n1(1);
    Struct s(Atom("s"), {&Y});
    X.match(&Y);
    Y.match(&Z);
    Y.match(&X);
    Y.match(&n1);
    EXPECT_FALSE(Y.match(&s));
    EXPECT_EQ("1", X.value());
    EXPECT_EQ("1", Y.value());
    EXPECT_EQ("1", Z.value());
    EXPECT_EQ("s(1)", s.value());
}

#endif