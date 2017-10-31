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

#endif
