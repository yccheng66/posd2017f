#ifndef EXP_H
#define EXP_H

#include "atom.h"

class MatchExp{
public:
  MatchExp(Term* left, Term* right): _left(left), _right(right){

  }

  bool evaluate(){
    return _left->match(*_right);
  }

private:
  Term* _left;
  Term* _right;
};

#endif
