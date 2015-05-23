#include <QString>
#include <QtTest>

extern "C" {
#include "fraction2.h"
#include "numberlib2.h"
}

class NumberLib2QTestTest : public QObject
{
    Q_OBJECT

public:
    NumberLib2QTestTest(){}

private Q_SLOTS:
    void testGCD(){
        QCOMPARE( greatestCommonDivisor(1u,1u), 1u);
        QCOMPARE( greatestCommonDivisor(3u,5u), 1u);
        QCOMPARE( greatestCommonDivisor(2u*3u,2u*5u), 2u);
        QCOMPARE( greatestCommonDivisor(2u*3u*5u*7u*11u*13u, 3u*7u*13u*17u), 3u*7u*13u);
    }

    void testFraction1()
    {
        struct fraction f1 = {1,1u,1u};
        struct fraction f2 = {1,1u,1u};
        struct fraction f3 = fractionMultiply(f1,f2);
        QCOMPARE( f3.status, FRACTION_OK );
        QCOMPARE( f3.sign, 1 );
        QCOMPARE( f3.numerator, 1u );
        QCOMPARE( f3.denominator, 1u );
    }

    void testFraction2()
    {
        struct fraction f1 = {1,2u,5u};
        struct fraction f2 = {-1,3u,7u};
        struct fraction f3 = fractionMultiply(f1,f2);
        QCOMPARE( f3.status, FRACTION_OK );
        QCOMPARE( f3.sign, -1 );
        QCOMPARE( f3.numerator, 2u * 3u );
        QCOMPARE( f3.denominator, 5u * 7u );
    }

    void testFraction3()
    {
        struct fraction f1 = {1,2u,5u};
        struct fraction f2 = {-1,5u,7u};
        struct fraction f3 = fractionMultiply(f1,f2);
        QCOMPARE( f3.status, FRACTION_OK );
        QCOMPARE( f3.sign, -1 );
        QCOMPARE( f3.numerator, 2u );
        QCOMPARE( f3.denominator, 7u );
    }

    void testFractionDenominatorZero1()
    {
        struct fraction f1 = {1,1u,0u};
        struct fraction f2 = {1,1u,1u};
        struct fraction f3 = fractionMultiply(f1,f2);
        QCOMPARE( f3.status, FRACTION_ERROR_DENOMINATOR_ZERO );
    }

    void testFractionDenominatorZero2()
    {
        struct fraction f1 = {1,1u,1u};
        struct fraction f2 = {1,1u,0u};
        struct fraction f3 = fractionMultiply(f1,f2);
        QCOMPARE( f3.status, FRACTION_ERROR_DENOMINATOR_ZERO );
    }

    void testFractionDenominatorOverflow()
    {
        struct fraction f1 = {1,1u,UINT_MAX/2+1};
        struct fraction f2 = {1,1u,2u};
        struct fraction f3 = fractionMultiply(f1,f2);
        QCOMPARE( f3.status, FRACTION_ERROR_OVERFLOW );
    }

    void testFractionNumeratorOverflow()
    {
        struct fraction f1 = {1,UINT_MAX/2+1,1u};
        struct fraction f2 = {1,2u,1u};
        struct fraction f3 = fractionMultiply(f1,f2);
        QCOMPARE( f3.status, FRACTION_ERROR_OVERFLOW );
    }

    void testFractionNestedError1()
    {
        struct fraction f1 = {1,1u,1u};
        struct fraction f2 = {1,1u,0u};
        struct fraction f3 = fractionMultiply(f1,f2);
        struct fraction f4 = fractionMultiply(f3,f1);
        QCOMPARE( f4.status, FRACTION_ERROR_DENOMINATOR_ZERO );
    }

    void testFractionNestedError2()
    {
        struct fraction f1 = {1,1u,1u};
        struct fraction f2 = {1,1u,0u};
        struct fraction f3 = fractionMultiply(f1,f2);
        struct fraction f4 = fractionMultiply(f1,f3);
        QCOMPARE( f4.status, FRACTION_ERROR_DENOMINATOR_ZERO );
    }
};


QTEST_APPLESS_MAIN(NumberLib2QTestTest)

#include "tst_numberlib2qtesttest.moc"
