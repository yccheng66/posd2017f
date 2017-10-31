#ifndef UTTERM_H
#define UTTERM_H

#include "../include/atom.h"
#include "../include/number.h"
#include "../include/variable.h"

// The symbol of Atom
TEST(atom, symbol)
{
    Atom tom("tom");
    EXPECT_EQ("tom", tom.symbol());
    Atom empty("");
    EXPECT_EQ("", empty.symbol());
}

// The value of Atom
TEST(atom, value)
{
    Atom tom("tom");
    EXPECT_EQ("tom", tom.value());
    Atom jerry("jerry");
    EXPECT_EQ("jerry", jerry.value());
}

// -? tom = tom.
// true.
// -? tom = jerry
// false.
TEST(atom, matchAtom)
{
    Atom tom("tom");
    EXPECT_TRUE(tom.match(&tom));
    Atom jerry("jerry");
    EXPECT_FALSE(tom.match(&jerry));
}

// -? tom = 123.
// false.
TEST(atom, matchNumber)
{
    Atom tom("tom");
    Number num(123);
    EXPECT_FALSE(tom.match(&num));
}

// -? tom = X, tom = X.
// X = tom.
// -? tom = X, jerry = X.
// false.
TEST(atom, matchVariable)
{
    Atom tom("tom");
    Variable X("X");
    EXPECT_TRUE(tom.match(&X));
    EXPECT_TRUE(tom.match(&X));
    Atom jerry("jerry");
    EXPECT_FALSE(jerry.match(&X));
}

// The symbol of number //
TEST(number, symbol)
{
    Number n1(-1);
    EXPECT_EQ("-1", n1.symbol());
    Number n2(0);
    EXPECT_EQ("0", n2.symbol());
    Number n3(1);
    EXPECT_EQ("1", n3.symbol());
}

// The value of number //
TEST(number, value)
{
    Number n1(-1);
    EXPECT_EQ("-1", n1.value());
    Number n2(0);
    EXPECT_EQ("0", n2.value());
    Number n3(1);
    EXPECT_EQ("1", n3.value());
}

// -? -1 = tom.
// false.
TEST(number, matchAtom)
{
    Number n(-1);
    Atom tom("tom");
    EXPECT_FALSE(n.match(&tom));
}

// -? -1 = -1.
// true.
// -? -1 = 1.
// false.
TEST(number, matchNumber)
{
    Number n1(-1);
    EXPECT_TRUE(n1.match(&n1));
    Number n2(1);
    EXPECT_FALSE(n1.match(&n2));
}

// -? -1 = X, -1 = X.
// X = -1.
// -? -1 = X, 0 = X.
// false.
TEST(number, matchVariable)
{
    Number n1(-1);
    Variable X("X");
    EXPECT_TRUE(n1.match(&X));
    EXPECT_TRUE(n1.match(&X));
    Number n2(0);
    EXPECT_FALSE(n2.match(&X));
}

// The symbol of variable //
TEST(variable, symbol)
{
    Variable X("X");
    EXPECT_EQ("X", X.symbol());
    Variable Y("Y");
    EXPECT_EQ("Y", Y.symbol());
}

// The default value of variable //
TEST(variable, defaultValue)
{
    Variable X("X");
    EXPECT_EQ("X", X.value());
    Variable Z("Z");
    EXPECT_EQ("Z", Z.value());
}

// -? X = tom, X = tom.
// X = tom.
// -? Y = tom, Y = jerry.
// false
TEST(variable, matchAtom)
{
    Variable X("X");
    Atom tom("tom");
    EXPECT_TRUE(X.match(&tom));
    EXPECT_TRUE(X.match(&tom));
    EXPECT_EQ("tom", X.value());
    Variable Y("Y");
    Atom jerry("jerry");
    EXPECT_TRUE(Y.match(&tom));
    EXPECT_FALSE(Y.match(&jerry));
    EXPECT_EQ("tom", Y.value());
}

// X = 123, X = 123.
// X = 123.
// Y = 123, Y = 456.
// false
TEST(variable, matchNumber)
{
    Variable X("X");
    Number n1(123);
    EXPECT_TRUE(X.match(&n1));
    EXPECT_TRUE(X.match(&n1));
    EXPECT_EQ("123", X.value());
    Variable Y("Y");
    Number n2(456);
    EXPECT_TRUE(Y.match(&n1));
    EXPECT_FALSE(Y.match(&n2));
    EXPECT_EQ("123", Y.value());
}

// -? X = X. (cycle detection)
// true.
TEST(variable, matchItself)
{
    Variable X("X");
    EXPECT_TRUE(X.match(&X));
    EXPECT_TRUE(X.match(&X));
    EXPECT_EQ("X", X.value());
}

// -? X = Y, X = Y. (cycle detection)
// X = Y.
TEST(variable, matchItselfFromOther)
{
    Variable X("X");
    Variable Y("Y");
    EXPECT_TRUE(X.match(&Y));
    EXPECT_TRUE(X.match(&Y));
    EXPECT_EQ("Y", X.value());
    EXPECT_EQ("Y", Y.value());
}

// -? X = Y, Y = X. (cycle detection)
// X = Y.
TEST(variable, matchCycle)
{
    Variable X("X");
    Variable Y("Y");
    EXPECT_TRUE(X.match(&Y));
    EXPECT_TRUE(Y.match(&X));
    EXPECT_EQ("Y", X.value());
    EXPECT_EQ("Y", Y.value());
}

// -? X = Y, Y = Z, Y = X. (cycle detection)
// X = Y, Y = Z.
TEST(variable, matchCycleInTheMiddle)
{
    Variable X("X");
    Variable Y("Y");
    Variable Z("Z");
    EXPECT_TRUE(X.match(&Y));
    EXPECT_TRUE(Y.match(&Z));
    EXPECT_TRUE(Y.match(&X));
    EXPECT_EQ("Z", X.value());
    EXPECT_EQ("Z", Y.value());
    EXPECT_EQ("Z", Z.value());
}

// X = 1, Y = 2, X = Y.
// false.
TEST(variable, matchVariableWithDifferentNumber)
{
    Variable X("X");
    Number n1(1);
    X.match(&n1);
    Variable Y("Y");
    Number n2(2);
    Y.match(&n2);
    EXPECT_FALSE(X.match(&Y));
    EXPECT_FALSE(Y.match(&X));
}

// -? X = 1, Y = 1, X = Y.
// X = Y, Y = 1.
TEST(variable, matchVariableWithTheSameNumber)
{
    Variable X("X");
    Variable Y("Y");
    Number n1(1);
    X.match(&n1);
    Y.match(&n1);
    EXPECT_TRUE(X.match(&Y));
    EXPECT_TRUE(Y.match(&X));
}

// -? X = tom, Y = jerry, X = Y.
// false.
TEST(variable, matchVariableWithDifferentAtom)
{
    Variable X("X");
    Atom tom("tom");
    X.match(&tom);
    Variable Y("Y");
    Atom jerry("jerry");
    Y.match(&jerry);
    EXPECT_FALSE(X.match(&Y));
    EXPECT_FALSE(Y.match(&X));
}

// -? X = tom, Y = tom, X = Y.
// X = Y, Y = tom.
TEST(variable, matchVariableWithTheSameVariable)
{
    Variable X("X");
    Variable Y("Y");
    Atom tom("tom");
    X.match(&tom);
    Y.match(&tom);
    EXPECT_TRUE(X.match(&Y));
    EXPECT_TRUE(Y.match(&X));
}

// -? X = Y, Y = Z, Y = 1.
// X = Y, Y = Z, Z = 1.
TEST(variable, matchInstanceInTheMiddle)
{
    Variable X("X");
    Variable Y("Y");
    Variable Z("Z");
    Number n1(1);
    X.match(&Y);
    Y.match(&Z);
    Y.match(&n1);
    EXPECT_EQ("1", X.value());
    EXPECT_EQ("1", Y.value());
    EXPECT_EQ("1", Z.value());
}

#endif
