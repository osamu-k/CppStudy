#include "gmock/gmock.h"

using namespace testing;

extern "C" {

void listAdd(
    int sign1, unsigned int numerator1, unsigned int denominator1,
    int sign2, unsigned int numerator2, unsigned int denominator2,
    int *signA, unsigned int *numeratorA, unsigned int *denominatorA )
{
    *signA = sign1;
    *numeratorA = numerator1 + numerator2;
    *denominatorA = denominator1;
}

}

TEST(Fraction, AddTwoFractionsCommonDenominator)
{
    int sign1 = 1;
    unsigned int numerator1 = 2;
    unsigned int denominator1 = 7;

    int sign2 = 1;
    unsigned int numerator2 = 3;
    unsigned int denominator2 = 7;

    int signA = 0;
    unsigned int numeratorA = 0;
    unsigned int denominatorA = 0;

    listAdd( sign1, numerator1, denominator1,
             sign2, numerator2, denominator2,
             &signA, &numeratorA, &denominatorA );

    ASSERT_THAT( signA, Eq(1) );
    ASSERT_THAT( numeratorA, Eq(5u) );
    ASSERT_THAT( denominatorA, Eq(7u) );
}

TEST(Fraction, AddAnotherTwoFractionsCommonDenominator)
{
    int sign1 = 1;
    unsigned int numerator1 = 3;
    unsigned int denominator1 = 5;

    int sign2 = 1;
    unsigned int numerator2 = 4;
    unsigned int denominator2 = 5;

    int signA = 0;
    unsigned int numeratorA = 0;
    unsigned int denominatorA = 0;

    listAdd( sign1, numerator1, denominator1,
             sign2, numerator2, denominator2,
             &signA, &numeratorA, &denominatorA );

    ASSERT_THAT( signA, Eq(1) );
    ASSERT_THAT( numeratorA, Eq(7u) );
    ASSERT_THAT( denominatorA, Eq(5u) );
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleMock(&argc,argv);
    return RUN_ALL_TESTS();
}

