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

// Brian Ma utTerm.h //
TEST(Number, ctor)
{
    Number n1(-1), n2(0), n3(01);
    ASSERT_EQ("-1", n1.value());
    ASSERT_EQ("0", n2.value());
    ASSERT_EQ("1", n3.value());

    Number n4(-1.0), n5(0.1030), n6(3.1234560), n7(1.414);
    ASSERT_EQ("-1", n4.value());
    ASSERT_EQ("0.103", n5.value());
    ASSERT_EQ("3.123456", n6.value());
    ASSERT_EQ("1.414", n7.value());

    Number n8(1.000000000001), n9(1.000005), n10(3.0100), n11(1.999999),
        n12(1.0000000000001);
    ASSERT_EQ("1.000000000001", n8.value());
    ASSERT_EQ("1.000005", n9.value());
    ASSERT_EQ("3.01", n10.value());
    ASSERT_EQ("1.999999", n11.value());
    ASSERT_EQ("1", n12.value());
}

// test Number.symbol()
TEST(Number, symbol)
{
    Number n1(-1), n2(0), n3(1);
    ASSERT_EQ("-1", n1.symbol());
    ASSERT_EQ("0", n2.symbol());
    ASSERT_EQ("1", n3.symbol());
}

//?- 25=25.
// true.
TEST(Number, matchSuccess)
{
    Number n1(25);
    Number n2(25);
    ASSERT_TRUE(n1.match(&n2));
}

//?- 25=0.
// false.
TEST(Number, matchFailureDiffValue)
{
    Number n1(25), n2(0);
    ASSERT_FALSE(n1.match(&n2));
}

//?- 25=tom.
// false.
TEST(Number, matchFailureDiffConstant)
{
    Number n1(-1);
    Atom a2("tom");
    ASSERT_FALSE(n1.match(&a2));
}

//?- 25=X.
// true.
TEST(Number, matchSuccessToVar)
{
    Number n1(25);
    Variable v2("X");
    ASSERT_TRUE(n1.match(&v2));
    ASSERT_EQ("25", v2.value());
    ASSERT_TRUE(n1.match(&v2));
}

//?- tom=25.
// false.
TEST(Atom, matchFailureDiffConstant)
{
    Atom a1("tom");
    Number n2(25);
    ASSERT_FALSE(a1.match(&n2));
}

// ?- tom = X.
// X = tom.
TEST(Atom, matchSuccessToVar)
{
    Atom a1("tom");
    Variable v2("X");
    ASSERT_TRUE(a1.match(&v2));
    ASSERT_EQ("tom", v2.value());
}

// ?- X=tom, tom=X.
// X = tom.
TEST(Atom, matchSuccessToVarInstantedToDiffConstant)
{
    Atom a1("tom");
    Variable v2("X");
    ASSERT_TRUE(v2.match(&a1));
    ASSERT_TRUE(a1.match(&v2));
    ASSERT_EQ("tom", v2.value());
}

// ?- X=jerry, tom=X.
// false.
TEST(Atom, matchFailureToVarInstantedToDiffConstant)
{
    Atom a1("tom"), a2("jerry");
    Variable v3("X");
    ASSERT_TRUE(v3.match(&a2));
    ASSERT_FALSE(a1.match(&v3));
    ASSERT_EQ("jerry", v3.value());
}

// ?- X = 5.
// X = 5.
TEST(Var, matchSuccessToNumber)
{
    Variable v1("X");
    Number n2(5);
    ASSERT_TRUE(v1.match(&n2));
    ASSERT_EQ("5", v1.value());
}

// ?- X=25, X= 100.
// false.
TEST(Var, matchFailureToTwoDiffNumbers)
{
    Variable v1("X");
    Number n2(25);
    Number n3(100);
    ASSERT_TRUE(v1.match(&n2));
    ASSERT_FALSE(v1.match(&n3));
    ASSERT_EQ("25", v1.value());
}

// ?- X=tom, X= 25.
// false.
TEST(Var, matchSuccessToAtomThenFailureToNumber)
{
    Variable v1("X");
    Atom a2("tom");
    Number n3(25);
    ASSERT_TRUE(v1.match(&a2));
    ASSERT_FALSE(v1.match(&n3));
    ASSERT_EQ("tom", v1.value());
}

//?- tom=X, 25=X.
// false.
TEST(Var, matchSuccessToAtomThenFailureToNumber2)
{
    Variable v1("X");
    Atom a2("tom");
    Number n3(25);
    ASSERT_TRUE(a2.match(&v1));
    ASSERT_FALSE(n3.match(&v1));
    ASSERT_EQ("tom", v1.value());
}

//?- X=tom, X=tom.
// true.
TEST(Var, reAssignTheSameAtom)
{
    Variable v1("X");
    Atom a2("tom");
    Atom a3("tom");
    ASSERT_TRUE(v1.match(&a2));
    ASSERT_TRUE(v1.match(&a2));
    ASSERT_TRUE(v1.match(&a3));
    ASSERT_EQ("tom", v1.value());
}

//?- X=X.
// true.
TEST(Var, reAssignItself)
{
    Variable v1("X");
    ASSERT_TRUE(v1.match(&v1));
}

//?- X=X, X=Y, X=Z.
// X = Y, Y = Z
TEST(Var, reAssignDifferentVar)
{
    Variable v1("X"), v2("Y"), v3("Z");
    ASSERT_TRUE(v1.match(&v1));
    ASSERT_TRUE(v1.match(&v2));
    ASSERT_TRUE(v1.match(&v3));
}

#endif
