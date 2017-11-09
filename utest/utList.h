#ifndef UTLIST_H
#define UTLIST_H

/* unit testing of class list */
// the atom.h, variable.h and struct.h have been included in list.h //
#include "../include/number.h"
#include "../include/list.h"

// [] = .() //
// [1] = .(1, []) //
TEST(list, functorAndArgs)
{
    List e;
    EXPECT_EQ(".", e.functor().symbol());
    EXPECT_EQ(0, e.arity());
    List l(new Number(1), &e);
    EXPECT_EQ(".", l.functor().symbol());
    EXPECT_EQ(2, l.arity());
    EXPECT_EQ("1", l.args(0)->symbol());
    EXPECT_EQ("[]", l.args(1)->symbol());
}

// [tom] = .(tom, []). //
// H = tom. //
TEST(list, head)
{
    List e;
    List l(new Atom("tom"), &e);
    EXPECT_EQ("tom", l.head()->symbol());
}

// [tom] = .(tom, []) //
// T = [] //
TEST(list, tail)
{
    List e;
    List l(new Atom("tom"), &e);
    EXPECT_EQ("[]", l.tail()->symbol());
}

// [] //
// head = throw exception //
TEST(list, headException)
{
    List e;
    try
    {
        e.head();
    }
    catch (string e)
    {
        EXPECT_EQ("Accessing head in an empty list", e);
    }
}

// [] //
// tail = throw exception //
TEST(list, tailException)
{
    List e;
    try
    {
        e.tail();
    }
    catch (string e)
    {
        EXPECT_EQ("Accessing tail in an empty list", e);
    }
}

// [] //
TEST(list, emptyList)
{
    List l;
    EXPECT_EQ("[]", l.symbol());
}

// [1, X, tom] //
TEST(list, listWithArgs)
{
    List e;
    List l0(new Atom("tom"), &e);
    List l1(new Variable("X"), &l0);
    List l2(new Number(1), &l1);
    EXPECT_EQ("[1, X, tom]", l2.symbol());
}

// [[[[]]]] //
TEST(list, nestedEmptyList)
{
    List e;
    List l0(&e, &e);
    List l1(&l0, &e);
    List l2(&l1, &e);
    EXPECT_EQ("[[[[]]]]", l2.symbol());
}

// [tom, [1, [[], s()], X]] //
// .(tom, .(.(1, .(.([], .(s(), [])), .(X, []))), []))  //
TEST(list, nestedList)
{
    Atom tom("tom");
    Number n(1);
    Variable X("X");
    Struct s(Atom("s"), {});
    List e;
    List l0(&s, &e);
    List l1(&e, &l0);
    List l2(&X, &e);
    List l3(&l1, &l2);
    List l4(&n, &l3);
    List l5(&l4, &e);
    List l6(&tom, &l5);
    EXPECT_EQ("[tom, [1, [[], s()], X]]", l6.symbol());
}

// -? [tom] = tom. //
// false. //
// -? [tom] = 1. //
// false. //
// [tom] = s(tom) //
// false. //
TEST(list, matchNonList)
{
    Atom tom("tom");
    Number n(1);
    Struct s(Atom("s"), {&tom});
    List e;
    List l(&tom, &e);
    EXPECT_FALSE(l.match(&tom));
    EXPECT_FALSE(l.match(&n));
    EXPECT_FALSE(l.match(&s));
}

// -? [tom] = []. //
// false. //
TEST(list, matchDifferentArgSize)
{
    List e;
    List l(new Atom("tom"), &e);
    EXPECT_FALSE(l.match(&e));
}

// -? [tom] = [jerry]. //
// false. //
TEST(list, matchDifferentArgs)
{
    List e;
    List l1(new Atom("tom"), &e);
    List l2(new Atom("jerry"), &e);
    EXPECT_FALSE(l1.match(&l2));
}

// -? [tom, 1, X] = [tom, 1, X]. //
// true. //
TEST(list, matchSuccess)
{
    Atom tom("tom");
    Number n(1);
    Variable X("X");
    List e;             // []
    List l0(&X, &e);    // .(X, [])
    List l1(&n, &l0);   // .(1, .(X, []))
    List l2(&tom, &l1); // .(tom, .(1, .(X, [])))
    List l3(&tom, &l1); // .(tom, .(1, .(X, [])))
    EXPECT_TRUE(l2.match(&l3));
}

// -? [tom, 1, X] = [tom, 1, s()]. //
// X = s(). //
TEST(list, matchWithVariableArg)
{
    Atom tom("tom");
    Number n(1);
    Variable X("X");
    Struct s(Atom("s"), {});
    List e;
    List l0(&X, &e);
    List l1(&n, &l0);
    List l2(&tom, &l1);
    List l3(&s, &e);
    List l4(&n, &l3);
    List l5(&tom, &l4);
    EXPECT_TRUE(l2.match(&l5));
    EXPECT_EQ("s()", X.value());
    EXPECT_EQ("[tom, 1, s()]", l2.value());
}

// -? [tom, X] = [X, tom]. //
// X = tom. //
TEST(list, matchWithVariableArg2)
{
    Atom tom("tom");
    Variable X("X");
    List e;
    List l0(&X, &e);
    List l1(&tom, &l0);
    List l2(&tom, &e);
    List l3(&X, &l2);
    EXPECT_TRUE(l1.match(&l3));
    EXPECT_EQ("tom", X.value());
}

// -? [tom, X] = [X, 1]. //
// false. //
TEST(list, matchWithVariableArg3)
{
    Atom tom("tom");
    Number n(1);
    Variable X("X");
    List e;
    List l0(&X, &e);
    List l1(&tom, &l0);
    List l2(&n, &e);
    List l3(&X, &l2);
    EXPECT_FALSE(l1.match(&l3));
    EXPECT_EQ("tom", X.value());
}

// -? [1] = [H|T]. //
// H = 1, T = []. //
TEST(list, matchHeadAndTail)
{
    List e;
    Number n(1);
    Variable H("H");
    Variable T("T");
    List l(&n, &e);
    Struct s(Atom("."), {&H, &T});
    EXPECT_TRUE(l.match(&s));
    EXPECT_EQ("1", H.value());
    EXPECT_EQ("[]", T.value());
}

// -? [1, 2] = [H|T]. //
// H = 1, T = [2]. //
TEST(list, matchHeadAndTail2)
{
    List e;
    Number n1(1);
    Number n2(2);
    Variable H("H");
    Variable T("T");
    List l0(&n2, &e);
    List l1(&n1, &l0);
    Struct s(Atom("."), {&H, &T});
    EXPECT_TRUE(l1.match(&s));
    EXPECT_EQ("1", H.value());
    EXPECT_EQ("[2]", T.value());
}

// -? [1, 2] = [1, H|T]. //
// H = 2, T = []. //
TEST(list, matchHeadAndTail3)
{
    List e;
    Number n1(1);
    Number n2(2);
    Variable H("H");
    Variable T("T");
    List l0(&n2, &e);
    List l1(&n1, &l0);
    Struct s0(Atom("."), {&H, &T});
    Struct s1(Atom("."), {&n1, &s0});
    EXPECT_TRUE(l1.match(&s1));
    EXPECT_EQ("2", H.value());
    EXPECT_EQ("[]", T.value());
}

// -? [1, 2] = [X|[Y|Z]]. //
// X = 1, Y = 2, Z = []. //
TEST(list, matchNestedHeadAndTail)
{
    Number n1(1);
    Number n2(2);
    Variable X("X");
    Variable Y("Y");
    Variable Z("Z");
    List e;
    List l0(&n2, &e);
    List l1(&n1, &l0);
    Struct s0(Atom("."), {&Y, &Z});
    Struct s1(Atom("."), {&X, &s0});
    EXPECT_TRUE(l1.match(&s1));
    EXPECT_EQ("1", X.value());
    EXPECT_EQ("2", Y.value());
    EXPECT_EQ("[]", Z.value());
}

#endif
