#ifndef UTATOM_H
#define UTATOM_H

/* unit testing of class atom */
#include "../include/atom.h"

// symbol of atom //
TEST(atom, symbol)
{
  Atom tom("tom");
  EXPECT_EQ("tom", tom.symbol());
}

// value of atom //
TEST(atom, value)
{
  Atom tom("tom");
  EXPECT_EQ("tom", tom.value());
}

// test the symbol and value of atom jerry //
TEST(atom, jerry)
{
  Atom jerry("jerry");
  EXPECT_EQ("jerry", jerry.symbol());
  EXPECT_EQ("jerry", jerry.value());
}

// -? tom = jerry. //
// false. //
// -? tom = tom //
// true. //
TEST(atom, match)
{
  Atom tom("tom");
  Atom jerry("jerry");
  EXPECT_FALSE(tom.match(&jerry));
  EXPECT_TRUE(tom.match(&tom));
}

#endif
