#include <QString>
#include <QtTest>

extern "C" {
#include "fraction.h"
#include "numberlib.h"
}

class NumberLibQTestTest : public QObject
{
    Q_OBJECT

public:
    NumberLibQTestTest(){}

private Q_SLOTS:

    void testGCD(){
        QCOMPARE( greatestCommonDivisor(1u,1u), 1u);
        QCOMPARE( greatestCommonDivisor(3u,5u), 1u);
        QCOMPARE( greatestCommonDivisor(2u*3u,2u*5u), 2u);
        QCOMPARE( greatestCommonDivisor(2u*3u*5u*7u*11u*13u, 3u*7u*13u*17u), 3u*7u*13u);
    }

    void testFractionMultiply1(){
        int sign;
        unsigned int numerator, denominator;
        int ret = fractionMuliply( 1, 1u, 1u,  1, 1u, 1u, &sign, &numerator, &denominator );
        QCOMPARE( ret, FRACTION_OK );
        QCOMPARE( sign, 1 );
        QCOMPARE( numerator, 1u );
        QCOMPARE( denominator, 1u );
    }

    void testFractionMultiply2(){
        int sign;
        unsigned int numerator, denominator;
        int ret = fractionMuliply( 1, 2u, 5u,  -1, 3u, 7u, &sign, &numerator, &denominator );
        QCOMPARE( ret, FRACTION_OK );
        QCOMPARE( sign, 1 * (-1) );
        QCOMPARE( numerator, 2u * 3u );
        QCOMPARE( denominator, 5u * 7u );
    }

    void testFractionMultiply3(){
        int sign;
        unsigned int numerator, denominator;
        int ret = fractionMuliply( 1, 2u, 5u,  -1, 5u, 7u, &sign, &numerator, &denominator );
        QCOMPARE( ret, FRACTION_OK );
        QCOMPARE( sign, 1 * (-1) );
        QCOMPARE( numerator, 2u );
        QCOMPARE( denominator, 7u );
    }

    void testFractionMultiplyDenominatorZero1(){
        int sign;
        unsigned int numerator, denominator;
        int ret = fractionMuliply( 1, 1u, 0u,  1, 1u, 1u, &sign, &numerator, &denominator );
        QCOMPARE( ret, FRACTION_ERROR_ZERO_DENOMINATOR );
    }

    void testFractionMultiplyDenominatorZero2(){
        int sign;
        unsigned int numerator, denominator;
        int ret = fractionMuliply( 1, 1u, 1u,  1, 1u, 0u, &sign, &numerator, &denominator );
        QCOMPARE( ret, FRACTION_ERROR_ZERO_DENOMINATOR );
    }

    void testFractionMultiplyDenominatorOverflow1(){
        int sign;
        unsigned int numerator, denominator;
        int ret = fractionMuliply(
                    1, 1u, UINT_MAX / 2 + 1,
                    1, 1u, 2,
                    &sign, &numerator, &denominator );
        QCOMPARE( ret, FRACTION_ERROR_OVERFLOW );
    }

    void testFractionMultiplyDenominatorOverflow2(){
        int sign;
        unsigned int numerator, denominator;
        int ret = fractionMuliply(
                    1, UINT_MAX / 2 + 1, 1u,
                    1, 2, 1u,
                    &sign, &numerator, &denominator );
        QCOMPARE( ret, FRACTION_ERROR_OVERFLOW );
    }
};

QTEST_APPLESS_MAIN(NumberLibQTestTest)

#include "tst_numberlibqtesttest.moc"
