#ifndef SCANNER_H
#define SCANNER_H

#include <utility>
#include <string>
#include "utility.h"
using std::string;
using std::pair;

class Scanner
{
public:
  Scanner(string in = "");
  pair<string, int> nextToken();
  int skipLeadingWhiteSpace();
  string extractNumber();
  string extractAtom();
  string extractAtomSC();
  string extractVariable();
  char extractChar();
  char currentChar();
  int position();

private:
  Utility *_utility;
  string _buffer;
  int _position;
};

#endif