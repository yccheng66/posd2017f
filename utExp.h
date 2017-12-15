#ifndef UTEXP_H
#define UTEXP_H

#include "atom.h"
#include "variable.h"
#include "exp.h"

TEST(Exp, matchExp) {
  Atom tom("tom");
  Variable X("X");
  MatchExp mExp(&tom, &X);
  ASSERT_TRUE(mExp.evaluate());
  ASSERT_EQ("tom", X.value());
}

#endif
