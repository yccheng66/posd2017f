#ifndef UTSCANNER_H
#define UTSCANNER_H

#include "scanner.h"

class ScannerTest : public ::testing::Test {
protected:
  void SetUp() {
    symtable.clear();
  }
};

TEST_F (ScannerTest, position) {
  // one, two, three spaces
  //---------------012345678901234567890
  Scanner scanner(" 12345,  tom,   Date");
  EXPECT_EQ(0, scanner.position());

  EXPECT_EQ(1, scanner.skipLeadingWhiteSpace());
  EXPECT_TRUE(isdigit(scanner.currentChar()));
  EXPECT_EQ(12345, scanner.extractNumber());
  EXPECT_EQ(6, scanner.position());

  EXPECT_EQ(',', scanner.extractChar());
  EXPECT_EQ(7, scanner.position());

  EXPECT_EQ(9, scanner.skipLeadingWhiteSpace());
  EXPECT_TRUE(islower(scanner.currentChar()));
  EXPECT_EQ("tom", scanner.extractAtom());
  EXPECT_EQ(12, scanner.position());

  EXPECT_EQ(',', scanner.extractChar());
  EXPECT_EQ(13, scanner.position());

  EXPECT_EQ(16, scanner.skipLeadingWhiteSpace());
  EXPECT_TRUE(isupper(scanner.currentChar()));
  EXPECT_EQ("Date", scanner.extractVar());
  EXPECT_EQ(20, scanner.position());
}

TEST_F(ScannerTest, nextTokenEOS) {
  //---------------01234
  Scanner scanner("    ");
  EXPECT_EQ(0, scanner.position());
  int token = scanner.nextToken();
  EXPECT_EQ(EOS, token);
  EXPECT_EQ(NONE, scanner.tokenValue());
  EXPECT_EQ(4, scanner.position());
}

TEST_F(ScannerTest, nextTokenEOS2) {
  //---------------0
  Scanner scanner("");
  EXPECT_EQ(0, scanner.position());
  int token = scanner.nextToken();
  EXPECT_EQ(EOS, token);
  EXPECT_EQ(NONE, scanner.tokenValue());
  EXPECT_EQ(0, scanner.position());
}

TEST_F(ScannerTest, nextTokenNumber) {
  //---------------0123
  Scanner scanner("135");
  EXPECT_EQ(0, scanner.position());
  int token = scanner.nextToken();
  EXPECT_EQ(NUMBER, token);
  EXPECT_EQ(135, scanner.tokenValue());
  EXPECT_TRUE(symtable.empty());
}

TEST_F(ScannerTest, nextTokenAtom) {
  //---------------0123
  Scanner scanner("tom");
  EXPECT_EQ(0, scanner.position());
  int token = scanner.nextToken();
  EXPECT_EQ(ATOM, token);
  EXPECT_EQ(0, scanner.tokenValue());
  EXPECT_EQ(3, scanner.position());
  EXPECT_EQ("tom", symtable[0].first);
  EXPECT_EQ(ATOM, symtable[0].second);
}

TEST_F(ScannerTest, nextTokenVar) {
  //---------------01234
  Scanner scanner("Date");
  EXPECT_EQ(0, scanner.position());
  int token = scanner.nextToken();
  EXPECT_EQ(VAR, token);
  EXPECT_EQ(0, scanner.tokenValue());
  EXPECT_EQ(4, scanner.position());
  EXPECT_EQ("Date", symtable[0].first);
  EXPECT_EQ(VAR, symtable[0].second);
}

TEST_F(ScannerTest, nextTokenChar) {
  //---------------01234
  Scanner scanner("   (");
  int token = scanner.nextToken();
  EXPECT_EQ('(', token);
  EXPECT_EQ(NONE, scanner.tokenValue());
  EXPECT_EQ(4, scanner.position());
  token = scanner.nextToken();
  EXPECT_EQ(EOS, token);
  EXPECT_EQ(NONE, scanner.tokenValue());
  EXPECT_EQ(4, scanner.position());
}

TEST_F(ScannerTest, nextTokenAtomSC) {
  //---------------01234567-890
  Scanner scanner(".*-><&$@\\?");
  EXPECT_EQ(0, scanner.position());
  int token = scanner.nextToken();
  EXPECT_EQ(ATOMSC, token);
  EXPECT_EQ(0, scanner.tokenValue());
  EXPECT_EQ(10, scanner.position());
  EXPECT_EQ(".*-><&$@\\?", symtable[0].first);
  EXPECT_EQ(ATOMSC, symtable[0].second);
}

#endif
