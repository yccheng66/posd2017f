#ifndef UTVARIABLE_H
#define UTVARIABLE_H
#include "variable.h"
#include "struct.h"
#include "atom.h"

TEST(Variable, constructor){
  Variable X("X");
  ASSERT_EQ("X", X.symbol());
  ASSERT_EQ("X", X.value());
}

TEST(Variable , matching){
  Atom tom("tom");
  Atom jerry("jerry");
  Variable X("X");
  ASSERT_TRUE(X.match(tom));
  ASSERT_EQ("X", X.symbol());
  ASSERT_EQ( "tom", X.value());
  ASSERT_TRUE(X.match(tom));
  ASSERT_FALSE(X.match(jerry));
}

TEST(Variable , atom_to_varX){
  Atom tom("tom");
  Variable X("X");
  ASSERT_TRUE(tom.match(X));
  ASSERT_EQ("X", X.symbol());
  ASSERT_EQ( "tom", X.value());
}

// ?- X=2.7182.
// X=2.7182
TEST(Variable , numE_to_varX){
  Number e(2.1782);
  Variable X("X");
  ASSERT_TRUE(e.match(X));
  ASSERT_EQ("X", X.symbol());
  ASSERT_EQ( "2.1782", X.value());
}

// ?- X=Y, X=1.
// Y=1
TEST (Variable, varY_to_varX_and_num1_to_varX) {
  Variable X("X");
  Variable Y("Y");
  ASSERT_TRUE(X.match(Y));
  ASSERT_EQ("X", X.symbol());
  ASSERT_EQ("Y", X.value());
  ASSERT_EQ("Y", Y.symbol());
  ASSERT_EQ("Y", Y.value());
  Number _1(1);
  ASSERT_TRUE(X.match(_1));
  ASSERT_EQ("1", X.value());
  ASSERT_EQ("1", Y.value());
}

// ?- X=Y, Y=1.
// X=1
TEST (Variable, varY_to_varX_and_num1_to_varY) {
  Variable X("X");
  Variable Y("Y");
  ASSERT_TRUE(X.match(Y));
  ASSERT_EQ("X", X.symbol());
  ASSERT_EQ("Y", X.value());
  ASSERT_EQ("Y", Y.symbol());
  ASSERT_EQ("Y", Y.value());
  Number _1(1);
  ASSERT_TRUE(Y.match(_1));
  ASSERT_EQ("1", X.value());
  ASSERT_EQ("1", Y.value());
}

// ?- X=X, X=1.
// X=1
TEST (Variable, varX_match_varX_and_num1_to_varX) {
  Variable X("X");
  Number _1(1);
  ASSERT_TRUE(X.match(X));
  ASSERT_TRUE(X.match(_1));
  ASSERT_EQ("1", X.value());
}

// ?- Y=1, X=Y.
// X=1
TEST (Variable, num1_to_varY_and_varX_match_varY) {
  Variable X("X");
  Variable Y("Y");
  Number _1(1);
  ASSERT_TRUE(Y.match(_1));
  ASSERT_TRUE(X.match(Y));
  ASSERT_EQ("1", X.value());
  ASSERT_EQ("1", Y.value());
}

// ?- X=Y, Y=Z, Z=1
// X=1, Y=1, Z=1
TEST (Variable, num1_to_varZ_to_varY_to_varX) {
  Variable X("X");
  Variable Y("Y");
  ASSERT_TRUE(X.match(Y));
  ASSERT_EQ("X", X.symbol());
  ASSERT_EQ("Y", X.value());
  ASSERT_EQ("Y", Y.symbol());
  ASSERT_EQ("Y", Y.value());
  Variable Z("Z");
  ASSERT_TRUE(Y.match(Z));
  Number _1(1);
  ASSERT_TRUE(Z.match(_1));
  ASSERT_EQ("1", X.value());
  ASSERT_EQ("1", Y.value());
  ASSERT_EQ("1", Z.value());
}

// ?- X=Y, X=Z, Z=1
// X=1, Y=1, Z=1
TEST (Variable, num1_to_varZ_to_varX_and_varY_to_varX) {
  Variable X("X");
  Variable Y("Y");
  ASSERT_TRUE(X.match(Y));
  ASSERT_EQ("X", X.symbol());
  ASSERT_EQ("Y", X.value());
  ASSERT_EQ("Y", Y.symbol());
  ASSERT_EQ("Y", Y.value());
  Variable Z("Z");
  ASSERT_TRUE(X.match(Z));
  Number _1(1);
  ASSERT_TRUE(Z.match(_1));
  ASSERT_EQ("1", X.value());
  ASSERT_EQ("1", Y.value());
  ASSERT_EQ("1", Z.value());
}

// ?- Y=X, X=Z, Z=1
// X=1, Y=1, Z=1
TEST (Variable, varX_to_varY_and_varZ_to_varX_and_num1_to_varZ) {
  Variable X("X");
  Variable Y("Y");
  Variable Z("Z");
  ASSERT_TRUE(Y.match(X));
  ASSERT_TRUE(X.match(Z));
  Number _1(1);
  ASSERT_TRUE(Z.match(_1));
  EXPECT_EQ("1", X.value());
  EXPECT_EQ("1", Y.value());
  EXPECT_EQ("1", Z.value());
}

// ?- X=Y, Z=W, Y=Z, Y=1
// W=1, X=1, Y=1, Z=1
TEST (Variable, varY_to_varX_and_varW_to_varZ_and_varZ_to_varY_and_num1_to_varY) {
  Variable X("X");
  Variable Y("Y");
  ASSERT_TRUE(X.match(Y));
  ASSERT_EQ("X", X.symbol());
  ASSERT_EQ("Y", X.value());
  ASSERT_EQ("Y", Y.symbol());
  ASSERT_EQ("Y", Y.value());
  Variable Z("Z");
  Variable W("W");
  ASSERT_TRUE(Z.match(W));
  ASSERT_TRUE(Y.match(Z));
  Number _1(1);
  ASSERT_TRUE(Y.match(_1));
  ASSERT_EQ("1", X.value());
  ASSERT_EQ("1", Y.value());
  ASSERT_EQ("1", Z.value());
  ASSERT_EQ("1", W.value());
}

TEST (Variable, Struct1) {
  Variable X("X");
  std::vector<Term *> v = {&X};
  Struct s(Atom("s"), v);
  Variable Y("Y");
  ASSERT_TRUE(Y.match(s));
  ASSERT_EQ("Y", Y.symbol());
  ASSERT_EQ( "s(X)", Y.value());
}

TEST (Variable, Struct2) {
  Variable X("X");
  std::vector<Term *> v = {&X};
  Struct s(Atom("s"), v);
  Variable Y("Y");
  ASSERT_TRUE(Y.match(s));
  ASSERT_EQ("Y", Y.symbol());
  ASSERT_EQ( "s(X)", Y.value());
  Atom t("teddy");
  X.match(t);
  ASSERT_EQ( "s(teddy)", Y.value());
}
#endif
