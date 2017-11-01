#ifndef NUMBER_H
#define NUMBER_H

#include <iomanip>
#include <sstream>
#include "term.h"
#include "variable.h"

class Number : public Term
{
public:
  Number(double value);
  string symbol();
  string value();
  bool match(Term *term);

private:
  string convertValueToString() const;
  double _value;
};

#endif