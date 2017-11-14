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

TEST_F(ParserTest, emptyStruct)
{
  std::vector<Term *> terms;
  Struct s(Atom("s"),terms);
  ASSERT_EQ("s()", s.symbol());
}
TEST_F(ParserTest, emptyStruct2)
{
  Scanner scanner("s()");
  Parser parser(scanner);
  ASSERT_EQ("s()", parser.createTerm()->symbol());
}
TEST_F(ParserTest, NestedStruct)
{
  Scanner scanner("s(s(1))");
  Parser parser(scanner);
  ASSERT_EQ("s(s(1))", parser.createTerm()->symbol());
}

TEST_F(ParserTest,ListOfTermsEmpty)
{
  Scanner scanner("");
  Parser parser(scanner);
  std::vector<Term *> terms=parser.getArgs();
  ASSERT_EQ(0,terms.size());
}
TEST_F(ParserTest,parseVar)
{
  Scanner scanner("_date");
  Parser parser(scanner);
  ASSERT_EQ("_date", parser.createTerm()->symbol());
}

TEST_F(ParserTest,listofTermsTwoNumber)
{
  Scanner scanner("12345 , 68");
  Parser parser(scanner);
  std::vector<Term *> terms=parser.getArgs();
  ASSERT_EQ("12345" , terms[0]->symbol());
  ASSERT_EQ("68" , terms[1]->symbol());

}

TEST_F( ParserTest,  parserStructOfStruct){
  Scanner scanner( "point(1, X, z(1,2,3))");
  Parser parser( scanner );
  std::vector<Term*> terms = parser.getArgs();
  ASSERT_EQ( "point(1, X, z(1, 2, 3))", terms[0]->symbol());
}

TEST_F( ParserTest, parserStructOfStructAllTheWay){
  Scanner scanner( "s(s(s(s(1))))");
  Parser parser( scanner );
  std::vector<Term*> terms = parser.getArgs();
  ASSERT_EQ( "s(s(s(s(1))))", terms[0]->symbol());
}
TEST_F(ParserTest, parserStructDotsTwoArgs){
  Scanner scanner("...(11,12)");
  Parser parser( scanner );
  std::vector<Term*> terms = parser.getArgs();
  ASSERT_EQ( "...(11, 12)", terms[0]->symbol());
  ASSERT_EQ( "...(11, 12)", terms[0]->symbol());
}
TEST_F(ParserTest, parserListEmpty){
  Scanner scanner("[]");
  Parser parser( scanner );
  std::vector<Term*> terms = parser.getArgs();
  ASSERT_EQ( "[]", terms[0]->symbol());
}
TEST_F(ParserTest, parserList){
  Scanner scanner("[1,2]");
  Parser parser( scanner );
  std::vector<Term*> terms = parser.getArgs();
  ASSERT_EQ( "[1, 2]", terms[0]->symbol());
}
TEST_F(ParserTest, parserListOfList){
  Scanner scanner("[[],[1]]");
  Parser parser( scanner );
  std::vector<Term*> terms = parser.getArgs();
  ASSERT_EQ( "[[], [1]]", terms[0]->symbol());
}
TEST_F(ParserTest, parserListOfListAndStruct){
  Scanner scanner("[[1],[],s(s(1))]");
  Parser parser( scanner );
  std::vector<Term*> terms = parser.getArgs();
  ASSERT_EQ( "[[1], [], s(s(1))]", terms[0]->symbol());
}
TEST_F(ParserTest, parserIllegal){
  Scanner scanner("[1,2)");
  Parser parser( scanner );
  ASSERT_ANY_THROW(parser.getArgs());
}









#endif
