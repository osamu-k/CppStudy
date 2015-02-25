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

void assertFractionAdd(
    int sign1, unsigned int numerator1, unsigned int denominator1,
    int sign2, unsigned int numerator2, unsigned int denominator2,
    int signExpected, unsigned numeratorExpected, unsigned denominatorExpected
)
{
    int signResult = 0;
    unsigned int numeratorResult = 0;
    unsigned int denominatorResult = 0;

    fractionAdd( sign1, numerator1, denominator1,
                 sign2, numerator2, denominator2,
                 &signResult, &numeratorResult, &denominatorResult );

    ASSERT_THAT( signResult, Eq(signExpected) );
    ASSERT_THAT( numeratorResult, Eq(numeratorExpected) );
    ASSERT_THAT( denominatorResult, Eq(denominatorExpected) );
}

TEST( Fraction, AddFractionsOfCommonDenominator1 )
{
    assertFractionAdd( +1, 1u, 5u,
                       +1, 2u, 5u,
                       +1, 3u, 5u );
}

TEST( Fraction, AddFractionsOfCommonDenominator2 )
{
    assertFractionAdd( +1, 2u, 7u,
                       +1, 3u, 7u,
                       +1, 5u, 7u );
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleMock(&argc,argv);
    return RUN_ALL_TESTS();
}

