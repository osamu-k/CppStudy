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
    unsigned int n1 = f1.numerator * f2.denominator;
    unsigned int n2 = f2.numerator * f1.denominator;
    if( f1.sign == f2.sign ){
        result.numerator = n1 + n2;
        result.sign = +1;
    }
    else{
        if( n1 >= n2 ){
            result.numerator = n1 - n2;
            result.sign = f1.sign;
        }
        else{
            result.numerator = n2 - n1;
            result.sign = f2.sign;
        }
    }
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

void assertFractionsEq( fraction f1, fraction f2 )
{
    ASSERT_THAT( f1.sign, f2.sign );
    ASSERT_THAT( f1.numerator, f2.numerator );
    ASSERT_THAT( f1.denominator, f2.denominator );
}

TEST( Fraction, AddFractionsOfCommonDenominator )
{
    fraction f1 = { +1, 2u, 7u };
    fraction f2 = { +1, 3u, 7u };
    fraction expected = { +1, 2u + 3u, 7u };

    assertFractionsEq( fractionAdd( f1, f2 ), expected );
}

TEST( Fraction, AddFractionsOfCommonDenominator2 )
{
    fraction f1 = { +1, 1u, 5u };
    fraction f2 = { +1, 2u, 5u };
    fraction expected = { +1, 1u + 2u, 5u };

    assertFractionsEq( fractionAdd( f1, f2 ), expected );
}

TEST( Fraction, AddFractionsOfDifferentDenominator )
{
    fraction f1 = { +1, 2u, 5u };
    fraction f2 = { +1, 3u, 7u };
    fraction expected = { +1, 2u * 7u + 3u * 5u, 5u * 7u };

    assertFractionsEq( fractionAdd( f1, f2 ), expected );
}

TEST( Fraction, AddFractionsResultReduced )
{
    fraction f1 = { +1, 1u, 12u };
    fraction f2 = { +1, 5u, 12u };
    fraction expected = { +1, 1u, 2u };

    assertFractionsEq( fractionAdd( f1, f2 ), expected );
}

TEST( Fraction, AddPositiveAndNegativeIsPositive )
{
    fraction f1 = { +1, 1u, 2u };
    fraction f2 = { -1, 1u, 3u };
    fraction expected = { +1, 1u, 6u };

    assertFractionsEq( fractionAdd( f1, f2 ), expected );
}

TEST( Fraction, AddPositiveAndNegativeIsNegative )
{
    fraction f1 = { +1, 1u, 3u };
    fraction f2 = { -1, 1u, 2u };
    fraction expected = { -1, 1u, 6u };

    assertFractionsEq( fractionAdd( f1, f2 ), expected );
}

TEST( Fraction, AddNegativeAndPositiveIsPositive )
{
    fraction f1 = { -1, 1u, 3u };
    fraction f2 = { +1, 1u, 2u };
    fraction expected = { +1, 1u, 6u };

    assertFractionsEq( fractionAdd( f1, f2 ), expected );
}

TEST( Fraction, AddNegativeAndPositiveIsNegative )
{
    fraction f1 = { -1, 1u, 2u };
    fraction f2 = { +1, 1u, 3u };
    fraction expected = { -1, 1u, 6u };

    assertFractionsEq( fractionAdd( f1, f2 ), expected );
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleMock(&argc,argv);
    return RUN_ALL_TESTS();
}
