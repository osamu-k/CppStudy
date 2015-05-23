#include "fraction.h"
#include "numberlib3.h"
#include "limits.h"

Fraction::Fraction()
    : m_sign(1)
    , m_numerator(1u)
    , m_denominator(1u)
{
}

Fraction::Fraction(int sign, unsigned int numerator, unsigned int denominator)
    : m_sign(1)
    , m_numerator(numerator)
    , m_denominator(denominator)
{
    if( denominator == 0 ){
        throw DenominatorZeroException();
    }
    if(sign < 0){
        m_sign = -1;
    }
    unsigned int gcd = greatestCommonDivisor( m_numerator, m_denominator );
    m_numerator /= gcd;
    m_denominator /= gcd;
}

Fraction::~Fraction()
{
}

Fraction Fraction::negate()
{
    return Fraction( - sign(), numerator(), denominator() );
}

Fraction Fraction::reciprocal()
{
    return Fraction( sign(), denominator(), numerator() );
}

Fraction Fraction::add(Fraction &other)
{
    Fraction f3;
    unsigned int n1 = multiply( numerator(), other.denominator() );
    unsigned int n2 = multiply( other.numerator(), denominator() );
    unsigned int d = multiply( denominator(), other.denominator() );
    if(sign() == other.sign()){
        f3 = Fraction ( sign(), add(n1,n2), d );
    }
    else if(n1 > n2){
        f3 = Fraction( sign(), n1 - n2, d );
    }
    else{
        f3 = Fraction( - sign(), n2 - n1, d );
    }
    return f3;
}

Fraction Fraction::subtract(Fraction &other)
{
    Fraction f = other.negate();
    return add( f );
}

Fraction Fraction::multiply(Fraction &other)
{
    Fraction f( m_sign * other.m_sign,
                multiply( m_numerator, other.m_numerator ),
                multiply( m_denominator, other.m_denominator ) );
    return f;
}

Fraction Fraction::divide(Fraction &other)
{
    Fraction f = other.reciprocal();
    return multiply(f);
}

Fraction Fraction::operator+(Fraction &other)
{
    return this->add(other);
}

Fraction Fraction::operator-(Fraction &other)
{
    return this->subtract(other);
}

Fraction Fraction::operator*(Fraction &other)
{
    return this->multiply(other);
}

Fraction Fraction::operator/(Fraction &other)
{
    return this->divide(other);
}

int Fraction::sign()
{
    return m_sign;
}

unsigned int Fraction::numerator()
{
    return m_numerator;
}

unsigned int Fraction::denominator()
{
    return m_denominator;
}

unsigned int Fraction::add(unsigned int x, unsigned int y)
{
    if( (UINT_MAX - x) < y ){
        throw OverflowException();
    }
    return x + y;
}

unsigned int Fraction::multiply(unsigned int x, unsigned int y)
{
    if( UINT_MAX / x < y ){
        throw OverflowException();
    }
    return x * y;
}
