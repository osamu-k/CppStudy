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
    fraction result;
    result.sign = +1;
    if( f1.denominator == f2.denominator ){
        result.numerator = f1.numerator + f2.numerator;
        result.denominator = f1.denominator;
    }
    else{
        result.numerator = f1.numerator * f2.denominator + f2.numerator * f1.denominator;
        result.denominator = f1.denominator * f2.denominator;
    }
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

int main(int argc, char **argv)
{
    ::testing::InitGoogleMock(&argc,argv);
    return RUN_ALL_TESTS();
}
