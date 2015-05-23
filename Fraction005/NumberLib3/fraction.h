#ifndef FRACTION_H
#define FRACTION_H


class Fraction
{
public:
    Fraction();
    Fraction(int sign, unsigned int numerator, unsigned int denominator);
    ~Fraction();

    Fraction negate();
    Fraction reciprocal();

    Fraction add(Fraction &other);
    Fraction subtract(Fraction &other);
    Fraction multiply(Fraction &other);
    Fraction divide(Fraction &other);

    Fraction operator+(Fraction &other);
    Fraction operator-(Fraction &other);
    Fraction operator*(Fraction &other);
    Fraction operator/(Fraction &other);

    int sign();
    unsigned int numerator();
    unsigned int denominator();

private:
    unsigned int add(unsigned int x, unsigned int y);
    unsigned int multiply(unsigned int x, unsigned int y);

    int m_sign;
    unsigned int m_numerator;
    unsigned int m_denominator;
};

class DenominatorZeroException
{
};

class OverflowException
{
};

#endif // FRACTION_H
