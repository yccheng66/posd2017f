#ifndef UTPARSER_H
#define UTPARSER_H

#include "../include/scanner.h"
#include "../include/parser.h"
#include "../include/prolog.h"

class ParserTest : public ::testing::Test
{
public:
  Prolog *prolog;
  pair<string, int> token;

protected:
  void SetUp()
  {
    prolog = Prolog::getInstance();
  }
};

TEST_F(ParserTest, createTerm_Var)
{
  Scanner scanner("X");
  Parser parser(scanner);
  ASSERT_EQ("X", parser.createTerm()->symbol());
}

TEST_F(ParserTest, createTerm_Num)
{
  Scanner scanner("123");
  Parser parser(scanner);
  ASSERT_EQ("123", parser.createTerm()->symbol());
}

TEST_F(ParserTest, createTerm_Atom)
{
  Scanner scanner("tom)");
  Parser parser(scanner);
  ASSERT_EQ("tom", parser.createTerm()->symbol());
}

TEST_F(ParserTest, createArgs)
{
  Scanner scanner("1, X, tom");
  Parser parser(scanner);
  vector<Term *> terms = parser.getArgs();
  ASSERT_EQ("1", terms[0]->symbol());
  ASSERT_EQ("X", terms[1]->symbol());
  ASSERT_EQ("tom", terms[2]->symbol());
}

TEST_F(ParserTest, createTerm_Struct)
{
  //...............012345678901
  Scanner scanner("s(1, X, tom)");
  Parser parser(scanner);
  EXPECT_EQ("s(1, X, tom)", parser.createTerm()->symbol());
}

TEST_F(ParserTest, createTerm_Nested_Struct)
{
  Scanner scanner("s(s(X, s(1, s(tom))))");
  Parser parser(scanner);
  ASSERT_EQ("s(s(X, s(1, s(tom))))", parser.createTerm()->symbol());
}

#endif
