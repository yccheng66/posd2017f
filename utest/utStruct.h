#ifndef UTSTRUCT_H
#define UTSTRUCT_H

/* unit testing of class struct */
// the atom.h and variable.h have been included in struct.h //
#include "../include/struct.h"
#include "../include/number.h"

// functor of struct //
TEST(structure, functor)
{
    Struct s(Atom("q"), {});
    EXPECT_EQ("q", s.functor().symbol());
}

// arity of struct //
TEST(structure, arity)
{
    Struct s1(Atom("s1"), {new Atom("a"), new Atom("b")});
    Struct s2(Atom("s2"), {});
    EXPECT_EQ(2, s1.arity());
    EXPECT_EQ(0, s2.arity());
}

// args of struct //
TEST(structure, args)
{
    Struct s(Atom("s"), {new Atom("a")});
    EXPECT_EQ("a", s.args(0)->symbol());
    EXPECT_FALSE(s.args(1));
}

// the empty struct //
TEST(structure, empty)
{
    Struct s(Atom("s"), {});
    EXPECT_EQ("s", s.functor().symbol());
    EXPECT_EQ(nullptr, s.args(0));
    EXPECT_EQ(0, s.arity());
    EXPECT_EQ("s()", s.symbol());
    EXPECT_EQ("s()", s.value());
}

// s(tom, 0.87, X) //
TEST(structure, structWithArgs)
{
    Atom tom("tom");
    Number n(0.87);
    Variable X("X");
    Struct s(Atom("s"), {&tom, &n, &X});
    EXPECT_EQ(3, s.arity());
    EXPECT_EQ("s(tom, 0.87, X)", s.symbol());
    EXPECT_EQ("s(tom, 0.87, X)", s.value());
}

// s(tom, 0.87, X), X = jerry //
// s(tom, 0.87, jerry) //
TEST(structure, valueWithSelfIndentifyingVariable)
{
    Atom tom("tom");
    Number n(0.87);
    Variable X("X");
    Struct s(Atom("s"), {&tom, &n, &X});
    Atom jerry("jerry");
    X.match(&jerry);
    EXPECT_EQ("s(tom, 0.87, jerry)", s.value());
}

// s3(s2(s1(s0()))) //
TEST(structure, nestemptyStruct)
{
    Struct s0(Atom("s0"), {});
    Struct s1(Atom("s1"), {&s0});
    Struct s2(Atom("s2"), {&s1});
    Struct s3(Atom("s3"), {&s2});
    EXPECT_EQ("s3(s2(s1(s0())))", s3.symbol());
}

// s3(s2(tom, s1(-1, X, s0()), -1), tom) //
TEST(structure, nestedStruct)
{
    Atom tom("tom");
    Number n(-1);
    Variable X("X");
    Struct s0(Atom("s0"), {});
    Struct s1(Atom("s1"), {&n, &X, &s0});
    Struct s2(Atom("s2"), {&tom, &s1, &n});
    Struct s3(Atom("s3"), {&s2, &tom});
    EXPECT_EQ("s3(s2(tom, s1(-1, X, s0()), -1), tom)", s3.symbol());
}

// -? s() = s //
// false. //
// -? s() = 0 //
// false. //
TEST(structure, matchNonStruct)
{
    Struct s(Atom("s"), {});
    Atom sAtom("s");
    Number n(0);
    EXPECT_FALSE(s.match(&sAtom));
    EXPECT_FALSE(s.match(&n));
}

// -? s1() = s2(). //
// false. //
TEST(structure, matchDifferentFunctor)
{
    Struct s1(Atom("s1"), {});
    Struct s2(Atom("s2"), {});
    EXPECT_FALSE(s1.match(&s2));
}

// -? s() = s(tom). //
// false. //
TEST(structure, matchDifferentArgSize)
{
    Struct s1(Atom("s"), {});
    Struct s2(Atom("s"), {new Atom("tom")});
    EXPECT_FALSE(s1.match(&s2));
}

// -? s(tom, jerry) = s(jerry, tom). //
// false. //
TEST(structure, matchDifferentArgs)
{
    Atom tom("tom");
    Atom jerry("jerry");
    Struct s1(Atom("s"), {&tom, &jerry});
    Struct s2(Atom("s"), {&jerry, &tom});
    EXPECT_FALSE(s1.match(&s2));
}

// -? s(tom, 1, X) = s(tom, 1, X) //
// true. //
TEST(structure, matchSuccess)
{
    Atom tom("tom");
    Number n(1);
    Variable X("X");
    Struct s1(Atom("s"), {&tom, &n, &X});
    Struct s2(Atom("s"), {&tom, &n, &X});
    EXPECT_TRUE(s1.match(&s2));
}

// -? s(X, 1) = s(tom, 1). //
// X = tom. //
TEST(structure, matchWithVariableArg)
{
    Variable X("X");
    Atom tom("tom");
    Number n(1);
    Struct s1(Atom("s"), {&X, &n});
    Struct s2(Atom("s"), {&tom, &n});
    EXPECT_TRUE(s1.match(&s2));
    EXPECT_EQ("tom", X.value());
}

// -? s(X, 1) = s(1, X). //
// X = 1. //
TEST(structure, matchWithVariableArg2)
{
    Variable X("X");
    Number n(1);
    Struct s1(Atom("s"), {&X, &n});
    Struct s2(Atom("s"), {&n, &X});
    EXPECT_TRUE(s1.match(&s2));
    EXPECT_EQ("1", X.value());
}

// -? s(X, 1) = s(tom, X). //
// false. //
TEST(structure, matchWithVariableArg3)
{
    Atom tom("tom");
    Variable X("X");
    Number n(1);
    Struct s1(Atom("s"), {&X, &n});
    Struct s2(Atom("s"), {&tom, &X});
    EXPECT_FALSE(s1.match(&s2));
    EXPECT_EQ("tom", X.value());
}

// X = s(), X = s(tom) //
// false. //
TEST(structure, matchVariable)
{
    Struct s1(Atom("s"), {});
    Struct s2(Atom("s"), {new Atom("tom")});
    Variable X("X");
    EXPECT_TRUE(X.match(&s1));
    EXPECT_FALSE(X.match(&s2));
}

// .(H, T) is a special format for struct //
TEST(structure, isSpecialStruct)
{
    Atom tom("tom");
    Atom jerry("jerry");
    Atom marry("marry");
    Struct s1(Atom("."), {&tom});
    Struct s2(Atom("."), {&tom, &jerry});
    Struct s3(Atom("."), {&tom, &jerry, &marry});
    Struct s4(Atom(","), {&tom, &jerry});
    EXPECT_FALSE(s1.isSpecialStruct());
    EXPECT_TRUE(s2.isSpecialStruct());
    EXPECT_FALSE(s3.isSpecialStruct());
    EXPECT_FALSE(s4.isSpecialStruct());
}

// .(1, 2) //
// [1|2] //
TEST(structure, specialStruct)
{
    Struct s(Atom("."), {new Number(1), new Number(2)});
    EXPECT_EQ("[1|2]", s.symbol());
}

// .(1, .(2, .(3, 4))) //
// [1, 2, 3|4] //
TEST(structure, specialNestedStruct)
{
    Struct s0(Atom("."), {new Number(3), new Number(4)});
    Struct s1(Atom("."), {new Number(2), &s0});
    Struct s2(Atom("."), {new Number(1), &s1});
    EXPECT_EQ("[1, 2, 3|4]", s2.symbol());
}

// .(1, []) = [1] //
TEST(structure, list)
{
    Number n(1);
    Struct e(Atom("."), {}); // empty list is not the .() in prolog //
    Struct s(Atom("."), {&n, &e});
    EXPECT_EQ("[1]", s.symbol());
}

#endif
