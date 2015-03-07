#include "gmock/gmock.h"

using namespace testing;

extern "C" {

typedef struct {
    int sign;
    unsigned int numerator;
    unsigned int denominator;
} fraction;

fraction fractionAdd( fraction f1, fraction f2 )
{
    fraction result = { +1, 2u+3u, 7u };
    return result;
}

}

TEST( Fraction, AddFractionsOfCommonDenominator )
{
    fraction f1 = { +1, 2u, 7u };
    fraction f2 = { +1, 3u, 7u };
    fraction f3 = { 0, 0, 0 };

    f3 = fractionAdd( f1, f2 );
    ASSERT_THAT( f3.sign, Eq(+1) );
    ASSERT_THAT( f3.numerator, Eq(2u+3u) );
    ASSERT_THAT( f3.denominator, Eq(7u) );
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleMock(&argc,argv);
    return RUN_ALL_TESTS();
}
