#ifndef UTNUMBER_H
#define UTNUMBER_H

/* unit testing of class number */
#include "../include/number.h"

// symbol of number //
TEST(number, symbol)
{
    Number n1(1);
    Number n2(0.48763);
    Number n3(-0.9487);
    EXPECT_EQ("1", n1.symbol());
    EXPECT_EQ("0.48763", n2.symbol());
    EXPECT_EQ("-0.9487", n3.symbol());
}

// value of number //
TEST(number, value)
{
    Number n1(1);
    Number n2(0.48763);
    Number n3(-0.9487);
    EXPECT_EQ("1", n1.value());
    EXPECT_EQ("0.48763", n2.value());
    EXPECT_EQ("-0.9487", n3.value());
}

// -? 1 = -1. //
// false. //
// -? 0.5647 = 0.56478. //
// false. //
// -? 0.5647 = 0.56470. //
// true. //
TEST(number, match)
{
    Number n1(1);
    Number n2(-1);
    Number n3(0.5647);
    Number n4(0.56478);
    Number n5(0.56470);
    EXPECT_FALSE(n1.match(&n2));
    EXPECT_FALSE(n3.match(&n4));
    EXPECT_TRUE(n3.match(&n5));
}

#endif