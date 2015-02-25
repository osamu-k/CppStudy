#include "gmock/gmock.h"
#include "limits.h"
#include <stdio.h>

using namespace testing;

extern "C" {

void fractionAdd(
    int sign1, unsigned int numerator1, unsigned int denominator1,
    int sign2, unsigned int numerator2, unsigned int denominator2,
    int *signResult, unsigned *numeratorResult, unsigned *denominatorResult
)
{
    *signResult = sign1;
    *numeratorResult = numerator1 + numerator2;
    *denominatorResult = denominator1;
}

}

TEST( Fraction, AddFractionsOfCommonDenominator1 )
{
    int sign = 0;
    unsigned int numerator = 0;
    unsigned int denominator = 0;

    fractionAdd( +1, 1, 5,
                 +1, 2, 5,
                 &sign, &numerator, &denominator );

    ASSERT_THAT( sign, Eq(+1) );
    ASSERT_THAT( numerator, Eq(3u) );
    ASSERT_THAT( denominator, Eq(5u) );
}

TEST( Fraction, AddFractionsOfCommonDenominator2 )
{
    int sign = 0;
    unsigned int numerator = 0;
    unsigned int denominator = 0;

    fractionAdd( +1, 2, 7,
                 +1, 3, 7,
                 &sign, &numerator, &denominator );

    ASSERT_THAT( sign, Eq(+1) );
    ASSERT_THAT( numerator, Eq(5u) );
    ASSERT_THAT( denominator, Eq(7u) );
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleMock(&argc,argv);
    return RUN_ALL_TESTS();
}

