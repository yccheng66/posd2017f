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

#endif
