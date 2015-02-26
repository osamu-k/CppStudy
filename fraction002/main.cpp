#include "gmock/gmock.h"
#include "limits.h"
#include <stdio.h>

using namespace testing;

extern "C" {

unsigned int greatestCommonDivisor(
    unsigned int x,
    unsigned int y
)
{
    unsigned int big = (x < y) ? y : x;
    unsigned int small = (x < y) ? x : y;
    while( big % small ){
        unsigned int tmp = big % small;
        big = small;
        small = tmp;
    }
    return small;
}

void fractionAdd(
    int sign1, unsigned int numerator1, unsigned int denominator1,
    int sign2, unsigned int numerator2, unsigned int denominator2,
    int *signResult, unsigned *numeratorResult, unsigned *denominatorResult
)
{
    *signResult = sign1;
    if( sign2 > 0 ){
        *numeratorResult = numerator1 * denominator2 + numerator2 * denominator1;
    }else{
        if( (numerator1 * denominator2) >= (numerator2 * denominator1) ){
            *numeratorResult = numerator1 * denominator2 - numerator2 * denominator1;
            *signResult = +1;
        }
        else{
            *numeratorResult = numerator2 * denominator1 - numerator1 * denominator2;
            *signResult = -1;
        }
    }
    *denominatorResult = denominator1 * denominator2;
    unsigned int gcd = greatestCommonDivisor( *numeratorResult, *denominatorResult );
    *numeratorResult /= gcd;
    *denominatorResult /= gcd;
}

}

TEST( GCD, IsOneIfNoCommonDivisor )
{
    unsigned int gcd = greatestCommonDivisor( 5u, 7u );
    ASSERT_THAT( gcd, Eq(1u) );
}

TEST( GCD, IsProductOfAllCommonDivisor )
{
    unsigned int gcd = greatestCommonDivisor( 3u * 5u * 7u, 5u * 7u * 11u );
    ASSERT_THAT( gcd, Eq(5u * 7u) );
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

TEST( Fraction, AddFractionsOfDifferentDenominator )
{
    assertFractionAdd( +1, 2u, 5u,
                       +1, 3u, 7u,
                       +1, (2u * 7u) + (3u * 5u), 5u * 7u );
}

TEST( Fraction, AddFractionsResultReduced )
{
    assertFractionAdd( +1, 1u, 6u,
                       +1, 1u, 3u,
                       +1, 1u, 2u );
}

TEST( Fraction, AddPositiveAndNegativeResultPositive )
{
    assertFractionAdd( +1, 1u, 2u,
                       -1, 1u, 3u,
                       +1, 1u, 6u );
}

TEST( Fraction, AddPositiveAndNegativeResultNegative )
{
    assertFractionAdd( +1, 1u, 3u,
                       -1, 1u, 2u,
                       -1, 1u, 6u );
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleMock(&argc,argv);
    return RUN_ALL_TESTS();
}

