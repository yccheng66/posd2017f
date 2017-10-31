#ifndef UTLIST_H
#define UTLIST_H

#include "../include/atom.h"
#include "../include/number.h"
#include "../include/variable.h"
#include "../include/struct.h"
#include "../include/list.h"

TEST(list, constructor)
{
    List list({});
    EXPECT_EQ(".", list.functor().symbol());
}

// [tom, jerry, marry]
TEST(list, symbol)
{
    Atom tom("tom");
    Atom jerry("jerry");
    Atom marry("marry");
    Atom emptyList("[]");
    List l({&marry, &emptyList});
    List l2({&jerry, &l});
    List l3({&tom, &l2});
    EXPECT_EQ("[tom, jerry, marry]", l3.symbol());
}

// [tom, jerry, marry]
TEST(list, value)
{
    Atom tom("tom");
    Atom jerry("jerry");
    Atom marry("marry");
    Atom emptyList("[]");
    List l({&marry, &emptyList});
    List l2({&jerry, &l});
    List l3({&tom, &l2});
    EXPECT_EQ("[tom, jerry, marry]", l3.value());
}

// -? [tom, jerry, marry] = [H|T].
//  H = tom, T = [jerry, marry]
TEST(list, match)
{
    Atom tom("tom");
    Atom jerry("jerry");
    Atom marry("marry");
    Atom emptyList("[]");
    List l({&marry, &emptyList});
    List l2({&jerry, &l});
    List l3({&tom, &l2});
    Variable H("H");
    Variable T("T");
    Struct s(Atom("."), {&H, &T});
    EXPECT_TRUE(l3.match(&s));
    EXPECT_EQ("tom", H.value());
    EXPECT_EQ("[jerry, marry]", T.value());
}
/*TEST(list, symbol)
{
    List list({}, false);
    EXPECT_EQ("[]", list.symbol());
    Atom tom("tom");
    Number n1(1);
    Variable X("X");
    Struct s(Atom("s"), {&X});
    List l({&tom, &n1, &X, &s}, false);
    EXPECT_EQ("[tom, 1, X, s(X)]", l.symbol());
}

TEST(list, concatSymbol)
{
    Atom tom("tom");
    Number n1(1);
    Variable X("X");
    Struct s(Atom("s"), {&X});
    List l({&tom, &n1, &X, &s}, true);
    EXPECT_EQ("[tom, 1, X|s(X)]", l.symbol());
}

// [tom, 1, X, s(X)].
TEST(list, value)
{
    Atom tom("tom");
    Number n1(1);
    Variable X("X");
    Struct s(Atom("s"), {&X});
    List l({&tom, &n1, &X, &s}, false);
    EXPECT_EQ("[tom, 1, X, s(X)]", l.value());
}

// [tom, 1, X|s(X)].
TEST(list, concatValue)
{
    Atom tom("tom");
    Number n1(1);
    Variable X("X");
    Struct s(Atom("s"), {&X});
    List l({&tom, &n1, &X, &s}, true);
    EXPECT_EQ("[tom, 1, X|s(X)]", l.value());
}

// X = 1, [tom, 1, X, s(X)].
TEST(list, valueWithMatch)
{
    Atom tom("tom");
    Number n1(1);
    Variable X("X");
    Struct s(Atom("s"), {&X});
    X.match(&n1);
    List l({&tom, &n1, &X, &s}, false);
    EXPECT_EQ("[tom, 1, 1, s(1)]", l.value());
}

// X = 1, [tom, 1, X|s(X)].
TEST(list, concatValueWithMatch)
{
    Atom tom("tom");
    Number n1(1);
    Variable X("X");
    Struct s(Atom("s"), {&X});
    X.match(&n1);
    List l({&tom, &n1, &X, &s}, true);
    EXPECT_EQ("[tom, 1, 1|s(1)]", l.value());
}

// -? X = [X].
// X = [X].
TEST(list, match)
{
    Variable X("X");
    List l({&X}, false);
    EXPECT_TRUE(l.match(&X));
    EXPECT_EQ("[X]", X.value());
}

// -? X = [1, X, tom, s(X)], X = Y.
// X = [1, X, tom, s(X)].
TEST(list, match2)
{
    Number n1(1);
    Variable X("X");
    Atom tom("tom");
    Struct s(Atom("s"), {&X});
    Variable Y("Y");
    List l({&n1, &X, &tom, &s}, false);
    EXPECT_TRUE(X.match(&l));
    EXPECT_TRUE(X.match(&Y));
    //EXPECT_EQ("[1, X, tom, s(X)]", X.value());
    //EXPECT_EQ("[1, X, tom, s(X)]", Y.value());
}

// -? [tom, jerry, marry] =  [H|T].
// H = tom, Y = [jerry, marry].
TEST(list, concatMatch)
{
    Atom tom("tom");
    Atom jerry("jerry");
    Atom marry("marry");
    List l({&tom, &jerry, &marry}, false);
    Variable H("H");
    Variable T("T");
    List concat({&H, &T}, true);
    EXPECT_TRUE(l.match(&concat));
    EXPECT_EQ("tom", concat.args(0)->value());
    EXPECT_EQ("[jerry, marry]", concat.args(1)->value());
}

// -? [tom, jerry, marry] = [tom, jerry|T].
// T = [marry].
TEST(list, concatMatch2)
{
    Atom tom("tom");
    Atom jerry("jerry");
    Atom marry("marry");
    Variable T("T");
    List l({&tom, &jerry, &marry}, false);
    List concat({&tom, &jerry, &T}, true);
    EXPECT_TRUE(l.match(&concat));
    EXPECT_EQ("[marry]", concat.args(2)->value());
}

// -? [tom, jerry] = [tom, jerry|T].
// T = [].
TEST(list, concatMatch3)
{
    Atom tom("tom");
    Atom jerry("jerry");
    Variable T("T");
    List l({&tom, &jerry}, false);
    List concat({&tom, &jerry, &T}, true);
    EXPECT_TRUE(l.match(&concat));
    EXPECT_EQ("[]", concat.args(2)->value());
}

// -? [tom, jerry, marry] = [X|[Y|Z]].
// X = tom, Y = jerry, Z = [marry].
TEST(list, concatMatch4)
{
    Atom tom("tom");
    Atom jerry("jerry");
    Atom marry("marry");
    List l({&tom, &jerry, &marry}, false);
    Variable X("X");
    Variable Y("Y");
    Variable Z("Z");
    List subConcat({&Y, &Z}, true);
    List concat({&X, &subConcat}, true);
    EXPECT_TRUE(l.match(&concat));
    EXPECT_EQ("tom", concat.args(0)->value());
    EXPECT_EQ("jerry", subConcat.args(0)->value());
    EXPECT_EQ("[marry]", subConcat.args(1)->value());
}

// -? [tom, jerry] = [H|jerry].
// false.
TEST(list, concatMatch5)
{
    Atom tom("tom");
    Atom jerry("jerry");
    Variable H("H");
    List l({&tom, &jerry}, false);
    List concat({&H, &jerry}, true);
    EXPECT_FALSE(l.match(&concat));
}

// -? [[tom, jerry, marry]|[H|T]] = [[X|[Y|Z]]|[randy]]
// H = randy, T = [], X = tom, Y = jerry, Z = [marry].
TEST(list, concatMatch6)
{
    Atom tom("tom");
    Atom jerry("jerry");
    Atom marry("marry");
    Atom randy("randy");
    Variable H("H");
    Variable T("T");
    Variable X("X");
    Variable Y("Y");
    Variable Z("Z");
    List sublist({&tom, &jerry, &marry}, false);
    List sublist2({&H, &T}, true);
    List list({&sublist, &sublist2}, true);
    List sublist3({&Y, &Z}, true);
    List sublist4({&X, &sublist3}, true);
    List sublist5({&randy}, false);
    List list2({&sublist4, &sublist5}, true);
    EXPECT_TRUE(list.match(&list2));
    EXPECT_EQ("randy", H.value());
    EXPECT_EQ("[]", T.value());
    EXPECT_EQ("tom", X.value());
    EXPECT_EQ("jerry", Y.value());
    EXPECT_EQ("[marry]", Z.value());
}

// -? [H|T]=[X|Y].
// H = X, T = Y.
TEST(list, concatMatch7)
{
    Variable H("H");
    Variable T("T");
    Variable X("X");
    Variable Y("Y");
    List list({&H, &T}, true);
    List list2({&X, &Y}, true);
    EXPECT_TRUE(list.match(&list2));
    EXPECT_EQ("X", H.value());
    EXPECT_EQ("Y", T.value());
}*/

#endif