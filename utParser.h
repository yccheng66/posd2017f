#ifndef UTPARSER_H
#define UTPARSER_H

#include "parser.h"
#include "scanner.h"

class ParserTest : public ::testing::Test {
protected:
  void SetUp() {
    symtable.clear();
  }
};

TEST_F(ParserTest, createTerm_Var){
  Scanner scanner("X");
  Parser parser(scanner);
  ASSERT_EQ("X", parser.createTerm()->symbol());
}

TEST_F(ParserTest, createTerm_Num){
  Scanner scanner("123");
  Parser parser(scanner);
  ASSERT_EQ("123", parser.createTerm()->symbol());
}

TEST_F(ParserTest, createTerm_Atom)
{
  Scanner scanner("tom");
  Parser parser(scanner);
  ASSERT_EQ("tom", parser.createTerm()->symbol());
}
TEST_F(ParserTest, errorTerm)
{
  Scanner scanner("s(1, X, tom)");
  Parser parser(scanner);
  ASSERT_NE(nullptr, parser.createTerm());
}

TEST_F(ParserTest, createArgs)
{
  Scanner scanner("1, X, tom");
  Parser parser(scanner);
  vector<Term*> terms = parser.getArgs();
  ASSERT_EQ("1", terms[0]->symbol());
  ASSERT_EQ("X", terms[1]->symbol());
  ASSERT_EQ("tom", terms[2]->symbol());

}

TEST_F(ParserTest, createTerms)
{
  Scanner scanner("s(1, X, tom)");
  Parser parser(scanner);
  ASSERT_EQ("s(1, X, tom)", parser.createTerm()->symbol());
}

// TEST_F(ParserTest, emptyStruct)
// {
//   Scanner scanner("s()");
//   Parser parser(scanner);
//   ASSERT_EQ("s()", parser.createTerm()->symbol());
// }
TEST_F(ParserTest, NestedStruct)
{
  Scanner scanner("s(s(1))");
  Parser parser(scanner);
  ASSERT_EQ("s(s(1))", parser.createTerm()->symbol());
}


#endif
