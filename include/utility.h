#ifndef UTILITY_H
#define UTILITY_H

#include "list.h"

class Utility
{
public:
  const int NONE = -1;
  const int EOS = '\0';
  const int NUMBER = 256;
  const int ATOM = 257;
  const int ATOMSC = 258;
  const int VARIABLE = 259;
  static Utility *getInstance();
  bool isSpecialChar(char c);

protected:
  Utility();

private:
  static Utility *_instance;
};

#endif