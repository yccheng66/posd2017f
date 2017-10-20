#ifndef GLOBAL_H
#define GLOBAL_H

#include <algorithm>

using std::pair;

#include <string>
using std::string;

const int NONE = -1; // no tokenValue

// tokens return by the scanner
const int EOS = '\0';
const int NUMBER = 256;
const int ATOM = 257;
const int ATOMSC = 258;
const int VAR = 259;

#include <vector>
using std::vector;

vector<pair<string, int>> symtable;

bool isSpecialCh(char c) {
  return c == '+'
      // || c == '=' // ... the matching operator
         || c == '-'
         || c == '*'
         || c == '/'
         || c == '<'
         || c == '>'
         || c == '.'
         || c == '&'
         || c == '\\'
         || c == '~'
         || c == '^'
         || c == '$'
         || c == '#'
         || c == '@'
         || c == '?'
         || c == ':';
}

bool symbolExist(string s, int & val) {
  bool found = false;
  val = -1;
  vector<pair<string, int>>::iterator it = find_if(symtable.begin(), symtable.end(), [s](pair<string, int> ele) {
    return ele.first == s;
  });

  found = symtable.end() != it;
  if (found)
   val = it - symtable.begin();

  return found;
}

#endif
