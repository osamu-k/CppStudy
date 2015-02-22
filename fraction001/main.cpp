#include "gmock/gmock.h"

using namespace testing;

extern "C" {

unsigned int greatestCommonDivisor(
    unsigned int x,
    unsigned int y
)
{
    unsigned int small = (x < y) ? x : y;
    unsigned int big   = (x < y) ? y : x;

    if( (big % small) == 0 ){
        return small;
    }
    return 1u;
}

void listAdd(
    int sign1, unsigned int numerator1, unsigned int denominator1,
    int sign2, unsigned int numerator2, unsigned int denominator2,
    int *signA, unsigned int *numeratorA, unsigned int *denominatorA )
{
    *signA = sign1;
    if( denominator1 == denominator2 ){
        *numeratorA = numerator1 + numerator2;
        *denominatorA = denominator1;
    }
    else{
        *numeratorA = (numerator1 * denominator2) + (numerator2 * denominator1);
        *denominatorA = denominator1 * denominator2;
    }
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
    ASSERT_THAT( greatestCommonDivisor( 3u, 3u * 5u), 3u );
}

TEST(GreatestCommonDivisor, OfXYIsYIfYDividesX)
{
    ASSERT_THAT( greatestCommonDivisor( 3u * 5u, 3u ), 3u );
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

TEST(Fraction, DISABLED_AddTwoFractionsAnswerReduced)
{
    assertAdd( 1, 1u, 2u * 3u,
               1, 1u, 3u * 5u,
               1, 5u + 2u, 2u * 3u * 5u );
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleMock(&argc,argv);
    return RUN_ALL_TESTS();
}

