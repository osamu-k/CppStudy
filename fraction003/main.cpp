#include "gmock/gmock.h"

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

typedef struct {
    int sign;
    unsigned int numerator;
    unsigned int denominator;
} fraction;

fraction fractionAdd( fraction f1, fraction f2 )
{
    fraction result;
    result.sign = +1;
    result.numerator = f1.numerator * f2.denominator + f2.numerator * f1.denominator;
    result.denominator = f1.denominator * f2.denominator;
    unsigned int gcd = greatestCommonDivisor( result.numerator, result.denominator );
    result.numerator /= gcd;
    result.denominator /= gcd;
    return result;
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

TEST( Fraction, AddFractionsOfCommonDenominator2 )
{
    fraction f1 = { +1, 1u, 5u };
    fraction f2 = { +1, 2u, 5u };
    fraction f3 = { 0, 0, 0 };

    f3 = fractionAdd( f1, f2 );
    ASSERT_THAT( f3.sign, Eq(+1) );
    ASSERT_THAT( f3.numerator, Eq(1u+2u) );
    ASSERT_THAT( f3.denominator, Eq(5u) );
}

TEST( Fraction, AddFractionsOfDifferentDenominator )
{
    fraction f1 = { +1, 2u, 5u };
    fraction f2 = { +1, 3u, 7u };
    fraction f3 = { 0, 0, 0 };

    f3 = fractionAdd( f1, f2 );
    ASSERT_THAT( f3.sign, Eq(+1) );
    ASSERT_THAT( f3.numerator, Eq(2u * 7u + 3u * 5u) );
    ASSERT_THAT( f3.denominator, Eq(5u * 7u) );
}

TEST( Fraction, AddFractionsResultReduced )
{
    fraction f1 = { +1, 1u, 12u };
    fraction f2 = { +1, 5u, 12u };
    fraction f3 = { 0, 0, 0 };

    f3 = fractionAdd( f1, f2 );
    ASSERT_THAT( f3.sign, Eq(+1) );
    ASSERT_THAT( f3.numerator, Eq(1u) );
    ASSERT_THAT( f3.denominator, Eq(2u) );
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleMock(&argc,argv);
    return RUN_ALL_TESTS();
}
