#include <vector>
#include "atom.h"
#include "struct.h"

TEST(Struct, hobby)
{
  Atom tom("tom");
  Atom chaseMouse("chaseMouse");
  std::vector<Term *> v = {&tom, &chaseMouse};
  Struct hobby("hobby", v);
  ASSERT_EQ("hobby", hobby.name());
  ASSERT_EQ("tom", hobby.args(0)->symbol());
  ASSERT_EQ("chaseMouse", hobby.args(1)->symbol());

}
TEST(Struct,symbol)
{
  Atom tom("tom");
  Atom chaseMouse("chaseMouse");
  std::vector<Term *> v = {&tom, &chaseMouse};
  Struct hobby("hobby", v);
  ASSERT_EQ("hobby(tom, chaseMouse)",hobby.symbol());
}
