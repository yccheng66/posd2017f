#ifndef UTSCANNER_H
#define UTSCANNER_H

#include "../include/scanner.h"
#include "../include/utility.h"

class ScannerTest : public ::testing::Test
{
  public:
    Utility *utility;
    pair<string, int> token;

  protected:
    void SetUp()
    {
        utility = Utility::getInstance();
    }
};

TEST_F(ScannerTest, empty)
{
    /* If you want to call the constructor which has a default value. 
     * Notice the following situation:
     * When your class have two constructor A() and A(int a = 0), then
     * you try to create an instance like this "A a". It will show the
     * ambiguous error because the complier doesn't know which constructors
     * should be called in this situation. */

    /* The other issue of constructing is the instantiation. If 
     * you write the sentence A a() and try to call the public method
     * of A. It will show the a.method is a nonclass method. But I don't
     * know why it can't be instantiated. However, when you write the
     * sentence like A* a = new A(), then everything will be ok. */
    Scanner s;
    EXPECT_EQ(0, s.position());
}

TEST_F(ScannerTest, position)
{
    // one, two, three spaces
    //---------------012345678901234567890
    Scanner scanner(" 12345,  tom,   Date");
    EXPECT_EQ(0, scanner.position());

    EXPECT_EQ(1, scanner.skipLeadingWhiteSpace());
    EXPECT_TRUE(isdigit(scanner.currentChar()));
    EXPECT_EQ("12345", scanner.extractNumber());
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
    EXPECT_EQ("Date", scanner.extractVariable());
    EXPECT_EQ(20, scanner.position());
}

TEST_F(ScannerTest, nextTokenEOS)
{
    //---------------01234
    Scanner scanner("    ");
    EXPECT_EQ(0, scanner.position());
    token = scanner.nextToken();
    EXPECT_EQ("", token.first);
    EXPECT_EQ(utility->EOS, token.second);
    EXPECT_EQ(4, scanner.position());
}

TEST_F(ScannerTest, nextTokenEOS2)
{
    //---------------0
    Scanner scanner("");
    EXPECT_EQ(0, scanner.position());
    token = scanner.nextToken();
    EXPECT_EQ("", token.first);
    EXPECT_EQ(utility->EOS, token.second);
    EXPECT_EQ(0, scanner.position());
}

TEST_F(ScannerTest, nextTokenNumber)
{
    //---------01234567890
    Scanner s("12.45, 8763");
    token = s.nextToken();
    EXPECT_EQ("12.45", token.first);
    EXPECT_EQ(utility->NUMBER, token.second);
    token = s.nextToken();
    EXPECT_EQ(",", token.first);
    EXPECT_EQ(',', token.second);
    token = s.nextToken();
    EXPECT_EQ("8763", token.first);
    EXPECT_EQ(utility->NUMBER, token.second);
}

TEST_F(ScannerTest, nextTokenAtom)
{
    //---------------0123
    Scanner scanner("tom");
    EXPECT_EQ(0, scanner.position());
    token = scanner.nextToken();
    EXPECT_EQ("tom", token.first);
    EXPECT_EQ(utility->ATOM, token.second);
    EXPECT_EQ(3, scanner.position());
}

TEST_F(ScannerTest, nextTokenVar)
{
    //---------------01234
    Scanner scanner("Date");
    EXPECT_EQ(0, scanner.position());
    token = scanner.nextToken();
    EXPECT_EQ("Date", token.first);
    EXPECT_EQ(utility->VARIABLE, token.second);
    EXPECT_EQ(4, scanner.position());
}

TEST_F(ScannerTest, nextTokenChar)
{
    //---------------01234
    Scanner scanner("   (");
    token = scanner.nextToken();
    EXPECT_EQ("(", token.first);
    EXPECT_EQ('(', token.second);
    EXPECT_EQ(4, scanner.position());
    token = scanner.nextToken();
    EXPECT_EQ("", token.first);
    EXPECT_EQ(utility->EOS, token.second);
    EXPECT_EQ(4, scanner.position());
}

TEST_F(ScannerTest, nextTokenAtomSC)
{
    //---------------01234567-890
    Scanner scanner(".*-><&$@\\?");
    EXPECT_EQ(0, scanner.position());
    token = scanner.nextToken();
    EXPECT_EQ(".*-><&$@\\?", token.first);
    EXPECT_EQ(utility->ATOMSC, token.second);
    EXPECT_EQ(10, scanner.position());
}

#endif