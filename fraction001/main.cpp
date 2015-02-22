#include "gmock/gmock.h"
#include "limits.h"

using namespace testing;

extern "C" {

#define BIGGER(x,y) (((x) < (y)) ? (y) : (x))
#define SMALLER(x,y) (((x) < (y)) ? (x) : (y))

unsigned int greatestCommonDivisor(
    unsigned int x,
    unsigned int y
)
{
    unsigned int big   = BIGGER(x, y);
    unsigned int small = SMALLER(x, y);
    while( (big % small) != 0 ){
        x = small;
        y = big - small;
        big   = BIGGER(x, y);
        small = SMALLER(x, y);
    }
    return small;
}

void listAdd(
    int sign1, unsigned int numerator1, unsigned int denominator1,
    int sign2, unsigned int numerator2, unsigned int denominator2,
    int *signA, unsigned int *numeratorA, unsigned int *denominatorA )
{
    /*
    int n = sign1 * (int)(numerator1 * denominator2) + sign2 * (int)(numerator2 * denominator1);
    if( n >= 0 ){
        *signA = 1;
        *numeratorA = n;
    }
    else{
        *signA = -1;
        *numeratorA = - n;
    }
    */
    if( (sign1 > 0) && (sign2 > 0) ){
        *numeratorA = (numerator1 * denominator2) + (numerator2 * denominator1);
        *signA = 1;
    }
    else if( (sign1 < 0) && (sign2 < 0) ){
        *numeratorA = (numerator1 * denominator2) + (numerator2 * denominator1);
        *signA = -1;
    }
    else if( (sign1 > 0) && (sign2 < 0) ){
        if( (numerator1 * denominator2) >= (numerator2 * denominator1) ){
            *numeratorA = (numerator1 * denominator2) - (numerator2 * denominator1);
            *signA = 1;
        }
        else{
            *numeratorA = (numerator2 * denominator1) - (numerator1 * denominator2);
            *signA = -1;
        }
    }
    else {// if( (sign1 < 0) && (sign2 > 0) ){
        if( (numerator1 * denominator2) >= (numerator2 * denominator1) ){
            *numeratorA = (numerator1 * denominator2) - (numerator2 * denominator1);
            *signA = -1;
        }
        else{
            *numeratorA = (numerator2 * denominator1) - (numerator1 * denominator2);
            *signA = 1;
        }
    }


    *denominatorA = denominator1 * denominator2;
    unsigned int gcd = greatestCommonDivisor( *numeratorA, *denominatorA );
    *numeratorA /= gcd;
    *denominatorA /= gcd;
}

}

void assertAdd(
    int sign1, unsigned int numerator1, unsigned int denominator1,
    int sign2, unsigned int numerator2, unsigned int denominator2,
    int signExpected, unsigned int numeratorExpected, unsigned int denominatorExpected
)
{
    int signResult = 0;
    unsigned int numeratorResult = 0;
    unsigned int denominatorResult = 0;

    listAdd( sign1, numerator1, denominator1,
             sign2, numerator2, denominator2,
             &signResult, &numeratorResult, &denominatorResult );

    ASSERT_THAT( signResult, Eq(signExpected) );
    ASSERT_THAT( numeratorResult, Eq(numeratorExpected) );
    ASSERT_THAT( denominatorResult, Eq(denominatorExpected) );
}

TEST(GreatestCommonDivisor, IsOneWhenNoCommonDivisor)
{
    ASSERT_THAT( greatestCommonDivisor( 5u, 7u ), Eq( 1u ) );
}

TEST(GreatestCommonDivisor, OfXYIsXIfXDividesY)
{
    ASSERT_THAT( greatestCommonDivisor( 3u, 3u * 5u), Eq(3u) );
}

TEST(GreatestCommonDivisor, OfXYIsYIfYDividesX)
{
    ASSERT_THAT( greatestCommonDivisor( 3u * 5u, 3u ), Eq(3u) );
}

TEST(GreatestCommonDivisor, IsProductOfAllCommonDivisors)
{
    ASSERT_THAT( greatestCommonDivisor( 2u * 3u * 5u * 7u, 3u * 7u * 11u ), Eq(3u * 7u) );
}

TEST(Fraction, AddTwoFractionsCommonDenominator)
{
    assertAdd( 1, 2u, 7u,
               1, 3u, 7u,
               1, (2u + 3u), 7u );
}

TEST(Fraction, AddAnotherTwoFractionsCommonDenominator)
{
    assertAdd( 1, 3u, 5u,
               1, 4u, 5u,
               1, (3u + 4u), 5u );
}

TEST(Fraction, AddTwoFractionsDifferentDenominator)
{
    assertAdd( 1, 2u, 7u,
               1, 3u, 5u,
               1, (2u * 5u) + (3u * 7u), 7u * 5u );
}

TEST(Fraction, AddTwoFractionsAnswerReduced)
{
    assertAdd( 1, 1u, 2u * 3u,
               1, 1u, 3u * 5u,
               1, 5u + 2u, 2u * 3u * 5u );
}

TEST(Fraction, PositivePlusNegativeIsPositive)
{
    assertAdd( 1, 1u, 2u,
               -1, 1u, 3u,
               1, 1u, 6u );
}

TEST(Fraction, PositivePlusNegativeIsNegative)
{
    assertAdd( -1, 1u, 2u,
               1, 1u, 3u,
               -1, 1u, 6u );
}

TEST(Fraction, NegativePlusNegativeIsNegative)
{
    assertAdd( -1, 1u, 2u,
               -1, 1u, 3u,
               -1, 5u, 6u );
}

TEST(Fraction, AddResultHasMaxNumerator)
{
    assertAdd( 1, UINT_MAX - 1, 1u,
               1, 1u, 1u,
               1, UINT_MAX, 1u );
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleMock(&argc,argv);
    return RUN_ALL_TESTS();
}

