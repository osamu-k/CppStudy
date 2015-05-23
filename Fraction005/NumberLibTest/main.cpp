#include "gmock/gmock.h"

extern "C" {
#include "numberlib.h"
}

using namespace testing;

TEST( gcd, of1and1is1 )
{
    int gcd = greatestCommonDivisor(1,1);
    ASSERT_THAT(gcd,1);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleMock(&argc,argv);
    return RUN_ALL_TESTS();
}

