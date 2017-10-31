#include <gtest/gtest.h>
#include "../utest/utTerm.h"
#include "../utest/utStruct.h"
#include "../utest/utList.h"
#include "../utest/utScanner.h"
#include "../utest/utParser.h"
#include "../utest/utAtom.h"
#include "../utest/utVariable.h"

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
