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

// Brian Ma utStruct.h //
TEST(Struct, hobby)
{
    Atom tom("tom");
    Atom chaseMouse("chaseMouse");
    vector<Term *> v = {&tom, &chaseMouse};
    Struct hobby(Atom("hobby"), v);
    ASSERT_EQ("hobby", hobby.functor().symbol());
    ASSERT_EQ("tom", hobby.args(0)->symbol());
    ASSERT_EQ("chaseMouse", hobby.args(1)->symbol());
}

TEST(Struct, symbol)
{
    Atom tom("tom");
    Atom chaseMouse("chaseMouse");
    vector<Term *> v = {&tom, &chaseMouse};
    Struct hobby(Atom("hobby"), v);
    ASSERT_EQ("hobby(tom, chaseMouse)", hobby.symbol());
}

TEST(Struct, match1)
{
    Atom tom("tom");
    Atom chaseMouse("chaseMouse");
    vector<Term *> v = {&tom, &chaseMouse};
    Struct hobby(Atom("hobby"), v);
    Struct hobby2(Atom("hobby2"), v);
    EXPECT_FALSE(hobby.match(&hobby2));
}

TEST(Struct, match2)
{
    Atom tom("tom");
    Atom chaseMouse("chaseMouse");
    vector<Term *> v = {&tom, &chaseMouse};
    Struct hobby(Atom("hobby"), v);
    std::vector<Term *> v1 = {&tom};
    Struct hobby2(Atom("hobby"), v1);
    EXPECT_FALSE(hobby.match(&hobby2));
}

TEST(Struct, match3)
{
    Atom tom("tom");
    Atom chaseMouse("chaseMouse");
    vector<Term *> v = {&tom, &chaseMouse};
    Struct hobby(Atom("hobby"), v);
    vector<Term *> v1 = {&chaseMouse, &tom};
    Struct hobby2(Atom("hobby"), v1);
    EXPECT_FALSE(hobby.match(&hobby2));
}

TEST(Struct, match4)
{
    Atom tom("tom");
    Atom chaseMouse("chaseMouse");
    vector<Term *> v = {&tom, &chaseMouse};
    Struct hobby(Atom("hobby"), v);
    Struct hobby2(Atom("hobby"), v);
    EXPECT_TRUE(hobby.match(&hobby2));
}

TEST(Struct, match5)
{
    Atom tom("tom");
    Atom chaseMouse("chaseMouse");
    vector<Term *> v = {&tom, &chaseMouse};
    Struct hobby(Atom("hobby"), v);
    EXPECT_FALSE(hobby.match(&tom));
}

// When Struct s contains a Variable X
// Then #symbol() should return "s(X)"
// and #value() should also return "s(X)"
TEST(Struct, var)
{
    Variable X("X");
    vector<Term *> v = {&X};
    Struct s(Atom("s"), v);
    ASSERT_EQ("s(X)", s.symbol());
}

// Given there is Struct s contains a Variable X
// When Variable X matches an Atom "tom"
// Then #symbol() should return "s(X)"
// and #value() should also return "s(tom)"
TEST(Struct, var_match_atom)
{
    Variable X("X");
    Struct s(Atom("s"), vector<Term *>{&X});
    ASSERT_EQ("s(X)", s.value());
    Atom a1("tom");
    // ASSERT_TRUE(X.match(a1));
    // ASSERT_EQ("s(X)", s.symbol());
    // ASSERT_EQ("s(tom)", s.value());
}

// Given there are Struct s1 and Struct s2
// When Struct s1 contains Struct s2
// And Struct s2 contains a Variable X
// Then #symbol() of s1 should return "s1(s2(X))"
// and #value() of s1 should also return "s1(s2(X))"
TEST(Struct, nested_struct1)
{
    Variable X("X");
    vector<Term *> v1 = {&X};
    Struct s2(Atom("s2"), v1);
    vector<Term *> v2 = {&s2};
    Struct s1(Atom("s1"), v2);
    ASSERT_EQ("s1(s2(X))", s1.symbol());
    ASSERT_EQ("s1(s2(X))", s1.value());
}

// Given there are Struct s1 contains Struct s2
// And Struct s2 contains Variable X
// When Variable X matches an Atom "tom"
// Then #symbol() of s1 should return "s1(s2(X))"
// and #value() of s1 should return "s1(s2(tom))"
TEST(Struct, nested_struct2)
{
    Variable X("X");
    vector<Term *> v1 = {&X};
    Struct s2(Atom("s2"), v1);
    vector<Term *> v2 = {&s2};
    Struct s1(Atom("s1"), v2);
    Atom a1("tom");
    ASSERT_TRUE(X.match(&a1));
    ASSERT_EQ("s1(s2(X))", s1.symbol());
    ASSERT_EQ("s1(s2(tom))", s1.value());
}

// Given there are Struct s1 contains Struct s2
// And Struct s2 contains Variable X
// When Variable X matches an Number pi: 3.14
// Then #symbol() of s1 should return "s1(s2(X))"
// and #value() of s1 should return "s1(s2(3.14))"
TEST(Struct, nested_struct3)
{
    Variable X("X");
    vector<Term *> v1 = {&X};
    Struct s2(Atom("s2"), v1);
    vector<Term *> v2 = {&s2};
    Struct s1(Atom("s1"), v2);
    Number n1(3.14);
    ASSERT_TRUE(X.match(&n1));
    ASSERT_EQ("s1(s2(X))", s1.symbol());
    ASSERT_EQ("s1(s2(3.14))", s1.value());
}

// Given there are Struct s1 contains Struct s2 and Variable X
// And Struct s2 contains Variable Y
// When Variable X matches Variable Y
// And Variable X matches Atom "kent_beck"
// Then #symbol() of s1 should return "s1(s2(Y), X)"
// and #value() of s1 should return "s1(s2(kent_beck), kent_beck)"
TEST(Struct, nested_struct_and_multiVariable)
{
    Variable X("X"), Y("Y");

    vector<Term *> v1 = {&Y};
    Struct s2(Atom("s2"), v1);

    vector<Term *> v2 = {&s2, &X};
    Struct s1(Atom("s1"), v2);

    ASSERT_TRUE(X.match(&Y));

    Atom a1("kent_beck");
    ASSERT_TRUE(X.match(&a1));
    ASSERT_EQ("s1(s2(Y), X)", s1.symbol());
    ASSERT_EQ("s1(s2(kent_beck), kent_beck)", s1.value());
}

#endif