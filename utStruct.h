#include <vector>
#include "atom.h"
#include "variable.h"
#include "struct.h"

TEST(Struct, hobby)
{
  Atom tom("tom");
  Atom chaseMouse("chaseMouse");
  std::vector<Term *> v = {&tom, &chaseMouse};
  Struct hobby(Atom("hobby"), v);
  ASSERT_EQ("hobby", hobby.name().symbol());
  ASSERT_EQ("tom", hobby.args(0)->symbol());
  ASSERT_EQ("chaseMouse", hobby.args(1)->symbol());
}

TEST(Struct,symbol)
{
  Atom tom("tom");
  Atom chaseMouse("chaseMouse");
  std::vector<Term *> v = {&tom, &chaseMouse};
  Struct hobby(Atom("hobby"), v);
  ASSERT_EQ("hobby(tom, chaseMouse)",hobby.symbol());
}

TEST(Struct, match1)
{
  Atom tom("tom");
  Atom chaseMouse("chaseMouse");
  std::vector<Term *> v = {&tom, &chaseMouse};
  Struct hobby(Atom("hobby"), v);
  Struct hobby2(Atom("hobby2"), v);
  EXPECT_FALSE(hobby.match(hobby2));
}

TEST(Struct, match2){
  Atom tom("tom");
  Atom chaseMouse("chaseMouse");
  std::vector<Term *> v = {&tom, &chaseMouse};
  Struct hobby(Atom("hobby"), v);
  std::vector<Term *> v1 = {&tom};
  Struct hobby2(Atom("hobby"), v1);
  EXPECT_FALSE(hobby.match(hobby2));
}

TEST(Struct, match3){
  Atom tom("tom");
  Atom chaseMouse("chaseMouse");
  std::vector<Term *> v = {&tom, &chaseMouse};
  Struct hobby(Atom("hobby"), v);
  std::vector<Term *> v1 = { &chaseMouse,&tom};
  Struct hobby2(Atom("hobby"), v1);
  EXPECT_FALSE(hobby.match(hobby2));
}

TEST(Struct, match4)
{
  Atom tom("tom");
  Atom chaseMouse("chaseMouse");
  std::vector<Term *> v = {&tom, &chaseMouse};
  Struct hobby(Atom("hobby"), v);
  Struct hobby2(Atom("hobby"), v);
  EXPECT_TRUE(hobby.match(hobby2));
}

TEST(Struct, match5)
{
  Atom tom("tom");
  Atom chaseMouse("chaseMouse");
  std::vector<Term *> v = {&tom, &chaseMouse};
  Struct hobby(Atom("hobby"), v);
  EXPECT_FALSE(hobby.match(tom));
}

// When Struct s contains a Variable X
// Then #symbol() should return "s(X)"
// and #value() should also return "s(X)"
TEST(Struct, var)
{
  Variable X("X");
  std::vector<Term *> v = {&X};
  Struct s(Atom("s"), v);
  ASSERT_EQ("s(X)",s.symbol());
  ASSERT_EQ("s(X)",s.value());
}

// Given there is Struct s contains a Variable X
// When Variable X matches an Atom "tom"
// Then #symbol() should return "s(X)"
// and #value() should also return "s(tom)"
TEST(Struct, var_match_atom)
{
  Variable X("X");
  std::vector<Term *> v = {&X};
  Struct s(Atom("s"), v);
  ASSERT_EQ("s(X)",s.symbol());
  ASSERT_EQ("s(X)",s.value());
  Atom tom("tom");
  X.match(tom);
  ASSERT_EQ("s(tom)",s.value());
}

TEST(Struct, var_match_num)
{
  Variable X("X");
  std::vector<Term *> v = {&X};
  Struct s(Atom("s"), v);
  ASSERT_EQ("s(X)",s.symbol());
  ASSERT_EQ("s(X)",s.value());
  Number g0(9.80665);
  X.match(g0);
  ASSERT_EQ("s(9.80665)",s.value());
}

TEST(Struct, var_match_struct)
{
  Variable X("X");
  Atom eg("erich_gamma");
  std::vector<Term *> v2 = {&eg};
  Struct s2(Atom("s2"), v2);
  std::vector<Term *> v1 = {&X};
  Struct s1(Atom("s1"), v1);
  ASSERT_EQ("s1(X)",s1.symbol());
  ASSERT_EQ("s1(X)",s1.value());
  X.match(s2);
  ASSERT_EQ("s1(s2(erich_gamma))", s1.value());
}

// Given there are Struct s1 and Struct s2
// When Struct s1 contains Struct s2
// And Struct s2 contains a Variable X
// Then #symbol() of s1 should return "s1(s2(X))"
// and #value() of s1 should also return "s1(s2(X))"
TEST(Struct, nested_struct1)
{
  Variable X("X");
  std::vector<Term *> v = {&X};
  Struct s2(Atom("s2"), v);
  std::vector<Term *> v2 = {&s2};
  Struct s1(Atom("s1"), v2);

  ASSERT_EQ("s1(s2(X))",s1.symbol());
  ASSERT_EQ("s1(s2(X))",s1.value());
}

// Given there are Struct s1 contains Struct s2
// And Struct s2 contains Variable X
// When Variable X matches an Atom "tom"
// Then #symbol() of s1 should return "s1(s2(X))"
// and #value() of s1 should return "s1(s2(tom))"
TEST(Struct, nested_struct2)
{
  Variable X("X");
  std::vector<Term *> v = {&X};
  Struct s2(Atom("s2"), v);
  std::vector<Term *> v2 = {&s2};
  Struct s1(Atom("s1"), v2);

  ASSERT_EQ("s1(s2(X))",s1.symbol());
  ASSERT_EQ("s1(s2(X))",s1.value());
  Atom tom("tom");
  X.match(tom);
  ASSERT_EQ("s1(s2(X))",s1.symbol());
  ASSERT_EQ("s1(s2(tom))",s1.value());
}

// Given there are Struct s1 contains Struct s2
// And Struct s2 contains Variable X
// When Variable X matches an Number pi: 3.14
// Then #symbol() of s1 should return "s1(s2(X))"
// and #value() of s1 should return "s1(s2(3.14))"
TEST(Struct, nested_struct3)
{
  Variable X("X");
  std::vector<Term *> v = {&X};
  Struct s2(Atom("s2"), v);
  std::vector<Term *> v2 = {&s2};
  Struct s1(Atom("s1"), v2);

  ASSERT_EQ("s1(s2(X))",s1.symbol());
  ASSERT_EQ("s1(s2(X))",s1.value());
  Number pi(3.14);
  X.match(pi);
  ASSERT_EQ("s1(s2(X))",s1.symbol());
  ASSERT_EQ("s1(s2(3.14))",s1.value());
}

TEST(Struct, nested_struct4)
{
  Variable X("X");
  std::vector<Term *> v = {&X};
  Struct s2(Atom("s2"), v);

  std::vector<Term *> v2 = {&X};
  Struct s3(Atom("s3"), v);

  std::vector<Term *> v3 = {&s2, &s3};
  Struct s1(Atom("s1"), v3);
  Atom kb("kent_beck");
  X.match(kb);
  ASSERT_EQ("s1(s2(X), s3(X))",s1.symbol());
  ASSERT_EQ("s1(s2(kent_beck), s3(kent_beck))",s1.value());
}

// Given there are Struct s1 contains Struct s2 and Variable X
// And Struct s2 contains Variable Y
// When Variable X matches Variable Y
// And Variable X matches Atom "kent_beck"
// Then #symbol() of s1 should return "s1(s2(Y), X)"
// and #value() of s1 should return "s1(s2(kent_beck), kent_beck)"
TEST(Struct, nested_struct_and_multiVariable)
{
  Variable X("X");
  Variable Y("Y");
  std::vector<Term *> v = {&Y};
  Struct s2(Atom("s2"), v);
  std::vector<Term *> v2 = {&s2, &X};
  Struct s1(Atom("s1"), v2);
  Atom kb("kent_beck");
  X.match(Y);
  Y.match(kb);
  ASSERT_EQ("s1(s2(Y), X)",s1.symbol());
  ASSERT_EQ("s1(s2(kent_beck), kent_beck)",s1.value());
}

//?-s(X)=s(Y).
//X=Y.
TEST(Struct, matchWithVar)
{
  Variable X("X");
  Variable Y("Y");
  std::vector<Term *> v = {&X};
  Struct s1(Atom("s"), v);
  std::vector<Term *> v2 = {&Y};
  Struct s2(Atom("s"), v2);
  ASSERT_TRUE(s1.match(s2));
}
