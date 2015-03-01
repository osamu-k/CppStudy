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
    unsigned int n1 = numerator1 * denominator2;
    unsigned int n2 = numerator2 * denominator1;
    if( sign1 == sign2 ){
        *numeratorResult = n1 + n2;
        *signResult = sign1;
    }
    else{
        if( n1 >= n2 ){
            *numeratorResult = n1 - n2;
            *signResult = sign1;
        }
        else{
            *numeratorResult = n2 - n1;
            *signResult = - sign1;
        }
    }
    if( *numeratorResult != 0 ){
        *denominatorResult = denominator1 * denominator2;
        unsigned int gcd = greatestCommonDivisor( *numeratorResult, *denominatorResult );
        *numeratorResult /= gcd;
        *denominatorResult /= gcd;
    }
    else{
        *signResult = +1;
        *numeratorResult = 0;
        *denominatorResult = 1;
    }
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

TEST( Fraction, AddPositiveAndNegativeResultZero )
{
    assertFractionAdd( +1, 1u, 3u,
                       -1, 1u, 3u,
                       +1, 0u, 1u );
}

TEST( Fraction, AddNegativeAndPositiveResultPositive )
{
    assertFractionAdd( -1, 1u, 3u,
                       +1, 1u, 2u,
                       +1, 1u, 6u );
}

TEST( Fraction, AddNegativeAndPositiveResultNegative )
{
    assertFractionAdd( -1, 1u, 2u,
                       +1, 1u, 3u,
                       -1, 1u, 6u );
}

TEST( Fraction, AddNegativeAndPositiveResultZero )
{
    assertFractionAdd( -1, 1u, 3u,
                       +1, 1u, 3u,
                       +1, 0u, 1u );
}

TEST( Fraction, AddNegativeAndNegativeResultNegative )
{
    assertFractionAdd( -1, 1u, 2u,
                       -1, 1u, 3u,
                       -1, 5u, 6u );
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleMock(&argc,argv);
    return RUN_ALL_TESTS();
}

