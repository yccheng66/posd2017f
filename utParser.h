#ifndef UTPARSER_H
#define UTPARSER_H

#include <string>

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
  parser.createTerms();
  vector<Term*> terms = parser.getTerms();
  ASSERT_EQ("X", terms[0]->symbol());
}

TEST_F(ParserTest, createTerm_Num){
  Scanner scanner("123");
  Parser parser(scanner);
  parser.createTerms();
  vector<Term*> terms = parser.getTerms();
  ASSERT_EQ("123", terms[0]->symbol());
}

TEST_F(ParserTest, createTerm_Atom)
{
  Scanner scanner("tom");
  Parser parser(scanner);
  parser.createTerms();
  vector<Term*> terms = parser.getTerms();
  ASSERT_EQ("tom", terms[0]->symbol());
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
  parser.createTerms();
  vector<Term*> terms = parser.getTerms();
  ASSERT_EQ("1", terms[0]->symbol());
  ASSERT_EQ("X", terms[1]->symbol());
  ASSERT_EQ("tom", terms[2]->symbol());
}

TEST_F(ParserTest,ListOfTermsEmpty)
{
  Scanner scanner;
  Parser parser(scanner);
  parser.createTerms();
  vector<Term*> terms = parser.getTerms();
  ASSERT_EQ(0,terms.size());
}

TEST_F(ParserTest,parseVar)
{
  Scanner scanner("_date");
  Parser parser(scanner);
  parser.createTerms();
  vector<Term*> terms = parser.getTerms();
  ASSERT_EQ("_date", terms[0]->symbol());
}

TEST_F(ParserTest,listofTermsTwoNumber)
{
  Scanner scanner("12345 , 68");
  Parser parser(scanner);
  parser.createTerms();
  vector<Term*> terms = parser.getTerms();
  ASSERT_EQ("12345" , terms[0]->symbol());
  ASSERT_EQ("68" , terms[1]->symbol());
}

TEST_F(ParserTest, parseStructNoArg) {
  Scanner scanner("point()");
  Parser parser(scanner);
  parser.createTerms();
  vector<Term*> terms = parser.getTerms();
  EXPECT_EQ("point()",terms[0]->symbol());
}

TEST_F(ParserTest, parseStructOneArg) {
  Scanner scanner("point(11)");
  Parser parser(scanner);
  parser.createTerms();
  vector<Term*> terms = parser.getTerms();
  EXPECT_EQ("point(11)",terms[0]->symbol());
}

TEST_F(ParserTest, parseStructTwoArgs) {
  Scanner scanner("point(11,12)");
  Parser parser(scanner);
  parser.createTerms();
  vector<Term*> terms = parser.getTerms();
  EXPECT_EQ("point(11, 12)",terms[0]->symbol());
}

TEST_F(ParserTest, parseStructThreeArgs) {
  Scanner scanner("point(1, X, z)");
  Parser parser(scanner);
  parser.createTerms();
  vector<Term*> terms = parser.getTerms();
  EXPECT_EQ("point(1, X, z)",terms[0]->symbol());
}

TEST_F( ParserTest,  parserStructOfStruct){
  Scanner scanner( "point(1, X, z(1,2,3))");
  Parser parser( scanner );
  parser.createTerms();
  vector<Term*> terms = parser.getTerms();
  ASSERT_EQ( "point(1, X, z(1, 2, 3))", terms[0]->symbol());
}

TEST_F(ParserTest, emptyStruct)
{
  Scanner scanner("s()");
  Parser parser(scanner);
  parser.createTerms();
  vector<Term*> terms = parser.getTerms();
  ASSERT_EQ("s()", terms[0]->symbol());
}

TEST_F(ParserTest, createTerms)
{
  Scanner scanner("s(1, X, tom)");
  Parser parser(scanner);
  parser.createTerms();
  vector<Term*> terms = parser.getTerms();
  ASSERT_EQ("s(1, X, tom)", terms[0]->symbol());
}

TEST_F(ParserTest, NestedStruct)
{
  Scanner scanner("s(s(1))");
  Parser parser(scanner);
  parser.createTerms();
  vector<Term*> terms = parser.getTerms();
  ASSERT_EQ("s(s(1))", terms[0]->symbol());
}

TEST_F( ParserTest, parserStructOfStructAllTheWay){
  Scanner scanner( "s(s(s(s(1))))");
  Parser parser( scanner );
  parser.createTerms();
  vector<Term*> terms = parser.getTerms();
  ASSERT_EQ( "s(s(s(s(1))))", terms[0]->symbol());
}

TEST_F(ParserTest, parseStructOfStructAllTheWay2) {
  Scanner scanner("s(s(s(s(1)))), b(1,2,3)");
  Parser parser(scanner);
  parser.createTerms();
  vector<Term*> terms = parser.getTerms();
  EXPECT_EQ(2, terms.size());
  EXPECT_EQ("s(s(s(s(1))))",terms[0]->symbol());
  EXPECT_EQ("b(1, 2, 3)",terms[1]->symbol());
}

TEST_F(ParserTest, parserStructDotsTwoArgs){
  Scanner scanner("...(11,12)");
  Parser parser( scanner );
  parser.createTerms();
  vector<Term*> terms = parser.getTerms();
  ASSERT_EQ( "...(11, 12)", terms[0]->symbol());
}

TEST_F(ParserTest, parserListEmpty){
  Scanner scanner("   [   ]");
  Parser parser( scanner );
  parser.createTerms();
  vector<Term*> terms = parser.getTerms();
  ASSERT_EQ( "[]", terms[0]->symbol());
}

TEST_F(ParserTest, parserList){
  Scanner scanner("   [1, 2]");
  Parser parser( scanner );
  parser.createTerms();
  vector<Term*> terms = parser.getTerms();
  ASSERT_EQ( "[1, 2]", terms[0]->symbol());
}

TEST_F(ParserTest, parserListOfList){
  Scanner scanner("   [  [1], [] ]");
  Parser parser( scanner );
  parser.createTerms();
  vector<Term*> terms = parser.getTerms();
  ASSERT_EQ( "[[1], []]", terms[0]->symbol());
}

TEST_F(ParserTest, parserListOfListAndStruct){
  Scanner scanner("   [  [1], [], s(s(1)) ]   ");
  Parser parser( scanner );
  parser.createTerms();
  vector<Term*> terms = parser.getTerms();
  ASSERT_EQ( "[[1], [], s(s(1))]", terms[0]->symbol());
}

TEST_F(ParserTest, parserIllegal){
  Scanner scanner("[1,2)");
  Parser parser( scanner );
  try {
    parser.createTerms();
    ASSERT_TRUE(false) << "It should throw a string; \"unexpected token\" as exception.";
  } catch (std::string exception) {
    EXPECT_EQ(exception, std::string("unexpected token"));
  }
}

TEST_F(ParserTest, ListAsStruct) {
  Scanner scanner(".(1,[])");
  Parser parser(scanner);
  parser.createTerms();
  vector<Term*> terms = parser.getTerms();
  EXPECT_EQ(1, terms.size());
  EXPECT_EQ(".(1, [])", terms[0]->symbol());
  EXPECT_EQ(2, ((Struct *) terms[0])->arity());
  Number * n = dynamic_cast<Number *>(((Struct *) terms[0])->args(0));
  EXPECT_EQ("1", n->symbol());
  List * l = dynamic_cast<List *>(((Struct *) terms[0])->args(1));
  EXPECT_EQ("[]", l->symbol());
}

TEST_F(ParserTest, ListAsStruct2) {
  Scanner scanner(".(2,.(1,[]))");
  Parser parser(scanner);
  parser.createTerms();
  vector<Term*> terms = parser.getTerms();
  EXPECT_EQ(1, terms.size());
  EXPECT_EQ(".(2, .(1, []))", terms[0]->symbol());
  EXPECT_EQ(2, ((Struct *) terms[0])->arity());
  Number * n = dynamic_cast<Number *>(((Struct *) terms[0])->args(0));
  EXPECT_EQ("2", n->symbol());
  Struct * s = dynamic_cast<Struct *>(((Struct *) terms[0])->args(1));
  EXPECT_EQ(".(1, [])", s->symbol());
}


#endif
