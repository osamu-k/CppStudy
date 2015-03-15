#include "gmock/gmock.h"
#include <string>

using namespace testing;

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

class FractionException
{
public:
    FractionException( const char *message );
    const char *message();
private:
    std::string m;
};

FractionException::FractionException(const char *message)
    : m(message)
{
}

class FractionInvalidSignException : public FractionException
{
public:
    FractionInvalidSignException();
};

FractionInvalidSignException::FractionInvalidSignException()
    : FractionException( "sign must be +1 or -1." )
{
}

const char *FractionException::message()
{
    return m.c_str();
}

class Fraction {
public:
    Fraction( int sign, unsigned int numerator, unsigned int denominator );

    int sign();
    unsigned int numerator();
    unsigned int denominator();
    Fraction add( Fraction f );
    Fraction operator+( Fraction f );

private:
    int s;
    unsigned int n;
    unsigned int d;
};

Fraction::Fraction( int sign, unsigned int numerator, unsigned int denominator )
    : s(sign), n(numerator), d(denominator)
{
    if( (sign != +1) && (sign != -1) ){
        throw FractionInvalidSignException();
    }
}

int Fraction::sign()
{
    return s;
}

unsigned int Fraction::numerator()
{
    return n;
}

unsigned int Fraction::denominator()
{
    return d;
}

Fraction Fraction::add( Fraction f )
{
    unsigned int n1 = n * f.d;
    unsigned int n2 = f.n * d;
    int new_s;
    unsigned int new_n;

    if( s == f.s ){
        new_n = n1 + n2;
        new_s = s;
    }
    else{
        if( n1 >= n2 ){
            new_n = n1 - n2;
            new_s = s;
        }
        else{
            new_n = n2 - n1;
            new_s = f.s;
        }
    }
    unsigned int new_d = d * f.d;
    unsigned int gcd = greatestCommonDivisor( new_n, new_d );
    return Fraction( s, new_n / gcd, new_d / gcd );
}

Fraction Fraction::operator+( Fraction f )
{
    return add( f );
}

TEST( Fraction, AFractionCanBeCreatedAsPositive )
{
    Fraction f( +1, 3u, 5u );

    EXPECT_THAT( f.sign(), Eq(+1) );
    EXPECT_THAT( f.numerator(), Eq(3u) );
    EXPECT_THAT( f.denominator(), Eq(5u) );
}

TEST( Fraction, AFractionCanBeCreatedAsNegative )
{
    Fraction f( -1, 3u, 5u );

    EXPECT_THAT( f.sign(), Eq(-1) );
    EXPECT_THAT( f.numerator(), Eq(3u) );
    EXPECT_THAT( f.denominator(), Eq(5u) );
}

TEST( Fraction, AddFractionsOfCommonDeniminator )
{
    Fraction f1( +1, 2u, 7u );
    Fraction f2( +1, 3u, 7u );
    Fraction f3 = f1.add( f2 );

    EXPECT_THAT( f3.sign(), Eq(+1) );
    EXPECT_THAT( f3.numerator(), Eq(2u+3u) );
    EXPECT_THAT( f3.denominator(), Eq(7u) );
}

TEST( Fraction, AddFractionsOfDifferentDeniminator )
{
    Fraction f1( +1, 2u, 7u );
    Fraction f2( +1, 3u, 5u );
    Fraction f3 = f1.add( f2 );

    EXPECT_THAT( f3.sign(), Eq(+1) );
    EXPECT_THAT( f3.numerator(), Eq(2u*5u + 3u*7u) );
    EXPECT_THAT( f3.denominator(), Eq(7u*5u) );
}


TEST( Fraction, AddFractionsResultMustBeReduced )
{
    Fraction f1( +1, 1u, 12u );
    Fraction f2( +1, 5u, 12u );
    Fraction f3 = f1.add( f2 );

    EXPECT_THAT( f3.sign(), Eq(+1) );
    EXPECT_THAT( f3.numerator(), Eq(1u) );
    EXPECT_THAT( f3.denominator(), Eq(2u) );
}

TEST( Fraction, AddFractionsPositiveAndNegativeIsPositive )
{
    Fraction f1( +1, 1u, 2u );
    Fraction f2( -1, 1u, 3u );
    Fraction f3 = f1.add( f2 );

    EXPECT_THAT( f3.sign(), Eq(+1) );
    EXPECT_THAT( f3.numerator(), Eq(1u) );
    EXPECT_THAT( f3.denominator(), Eq(6u) );
}

TEST( Fraction, AddFractionsWithOperator )
{
    Fraction f1( +1, 1u, 2u );
    Fraction f2( -1, 1u, 3u );
    Fraction f3 = f1 + f2;

    EXPECT_THAT( f3.sign(), Eq(+1) );
    EXPECT_THAT( f3.numerator(), Eq(1u) );
    EXPECT_THAT( f3.denominator(), Eq(6u) );
}

TEST( Fraction, AddFractionsWithOperator2 )
{
    Fraction f3 = Fraction( +1, 1u, 2u ) + Fraction( -1, 1u, 3u );

    EXPECT_THAT( f3.sign(), Eq(+1) );
    EXPECT_THAT( f3.numerator(), Eq(1u) );
    EXPECT_THAT( f3.denominator(), Eq(6u) );
}

TEST( Fraction, InvalidSignException )
{
    ASSERT_THROW( Fraction f( 0, 1u, 2u ), FractionInvalidSignException );
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleMock(&argc,argv);
    return RUN_ALL_TESTS();
}

