#include <QString>
#include <QtTest>

#include "fraction.h"
#include "numberlib3.h"

class NumberLib3TestTest : public QObject
{
    Q_OBJECT

public:
    NumberLib3TestTest(){}

private Q_SLOTS:
    void testGCD(){
        QCOMPARE( greatestCommonDivisor(1u,1u), 1u);
        QCOMPARE( greatestCommonDivisor(3u,5u), 1u);
        QCOMPARE( greatestCommonDivisor(2u*3u,2u*5u), 2u);
        QCOMPARE( greatestCommonDivisor(2u*3u*5u*7u*11u*13u, 3u*7u*13u*17u), 3u*7u*13u);
    }

    void testFraction1()
    {
        Fraction f1(1,1u,1u);
        Fraction f2(1,1u,1u);
        Fraction f3 = f1.multiply(f2);
        QCOMPARE( f3.sign(), 1 );
        QCOMPARE( f3.numerator(), 1u );
        QCOMPARE( f3.denominator(), 1u );
    }

    void testFraction2()
    {
        Fraction f1(1,2u,5u);
        Fraction f2(-1,3u,7u);
        Fraction f3 = f1.multiply(f2);
        QCOMPARE( f3.sign(), -1 );
        QCOMPARE( f3.numerator(), 2u*3u );
        QCOMPARE( f3.denominator(), 5u*7u );
    }

    void testFraction3()
    {
        Fraction f1(1,2u,5u);
        Fraction f2(-1,5u,7u);
        Fraction f3 = f1.multiply(f2);
        QCOMPARE( f3.sign(), -1 );
        QCOMPARE( f3.numerator(), 2u );
        QCOMPARE( f3.denominator(), 7u );
    }

    void testFractionDenominatorZero1()
    {
        bool error = false;
        try{
            Fraction f1(1,1u,0u);
            Fraction f2(1,1u,1u);
            Fraction f3 = f1.multiply(f2);
            QFAIL("DenominatorZeroException is not thrown !");
        }
        catch(DenominatorZeroException){
            error = true;
        }
        QCOMPARE(error,true);
    }

    void testFractionDenominatorZero2()
    {
        bool error = false;
        try{
            Fraction f1(1,1u,1u);
            Fraction f2(1,1u,0u);
            Fraction f3 = f1.multiply(f2);
            QFAIL("DenominatorZeroException is not thrown !");
        }
        catch(DenominatorZeroException){
            error = true;
        }
        QCOMPARE(error,true);
    }

    void testFractionOverDenominatorflow()
    {
        bool error = false;
        try{
            Fraction f1(1,1u,UINT_MAX / 2 + 1);
            Fraction f2(1,1u,2u);
            Fraction f3 = f1.multiply(f2);
            QFAIL("OverflowException is not thrown !");
        }
        catch(OverflowException){
            error = true;
        }
        QCOMPARE(error,true);
    }

    void testFractionOverNumeratorflow()
    {
        bool error = false;
        try{
            Fraction f1(1, UINT_MAX / 2 + 1, 1u);
            Fraction f2(1, 2u, 1u);
            Fraction f3 = f1.multiply(f2);
            QFAIL("OverflowException is not thrown !");
        }
        catch(OverflowException){
            error = true;
        }
        QCOMPARE(error,true);
    }


    void testFractionOperator()
    {
        Fraction f1(1,2u,5u);
        Fraction f2(-1,5u,7u);

        Fraction f3 = f1 * f2;

        QCOMPARE( f3.sign(), -1 );
        QCOMPARE( f3.numerator(), 2u );
        QCOMPARE( f3.denominator(), 7u );
    }

    void testFractionAdd1()
    {
        Fraction f1(1,1u,1u);
        Fraction f2(1,1u,1u);

        Fraction f3 = f1.add(f2);

        QCOMPARE( f3.sign(), 1 );
        QCOMPARE( f3.numerator(), 2u );
        QCOMPARE( f3.denominator(), 1u );
    }

    void testFractionAdd2()
    {
        Fraction f1(1,2u,5u);
        Fraction f2(1,3u,7u);

        Fraction f3 = f1.add(f2);

        QCOMPARE( f3.sign(), 1 );
        QCOMPARE( f3.numerator(), 2u*7u+3u*5u );
        QCOMPARE( f3.denominator(), 5u*7u );
    }

    void testFractionAdd3()
    {
        Fraction f1(-1,2u,5u);
        Fraction f2(1,3u,7u);

        Fraction f3 = f1.add(f2);

        QCOMPARE( f3.sign(), 1 );
        QCOMPARE( f3.numerator(), -(2u*7u)+3u*5u );
        QCOMPARE( f3.denominator(), 5u*7u );
    }

    void testFractionAdd4()
    {
        Fraction f1(-1,2u,5u);
        Fraction f2(1,3u,7u);

        Fraction f3 = f2.add(f1);

        QCOMPARE( f3.sign(), 1 );
        QCOMPARE( f3.numerator(), 3u*5u-(2u*7u) );
        QCOMPARE( f3.denominator(), 5u*7u );
    }

    void testFractionAdd5()
    {
        Fraction f1(1,2u,5u);
        Fraction f2(-1,3u,7u);

        Fraction f3 = f1.add(f2);

        QCOMPARE( f3.sign(), -1 );
        QCOMPARE( f3.numerator(), (3u*5u)-(2u*7u) );
        QCOMPARE( f3.denominator(), 5u*7u );
    }

    void testFractionAdd6()
    {
        Fraction f1(1,2u,5u);
        Fraction f2(-1,3u,7u);

        Fraction f3 = f2.add(f1);

        QCOMPARE( f3.sign(), -1 );
        QCOMPARE( f3.numerator(), (3u*5u)-(2u*7u) );
        QCOMPARE( f3.denominator(), 5u*7u );
    }

    void testFractionAddOverflow1()
    {
        bool error = false;
        try{
            Fraction f1(1, UINT_MAX / 2 + 1, 1u);
            Fraction f2(1, 1u, 2u);
            Fraction f3 = f1.add(f2);
            QFAIL("OverflowException is not thrown !");
        }
        catch(OverflowException){
            error = true;
        }
        QCOMPARE(error,true);
    }

    void testFractionAddOverflow2()
    {
        bool error = false;
        try{
            Fraction f1(1, UINT_MAX / 2 + 1, 1u);
            Fraction f2(1, 1u, 2u);
            Fraction f3 = f2.add(f1);
            QFAIL("OverflowException is not thrown !");
        }
        catch(OverflowException){
            error = true;
        }
        QCOMPARE(error,true);
    }

    void testFractionAddOverflow3()
    {
        bool error = false;
        try{
            Fraction f1(1, 1u, UINT_MAX / 2 + 1);
            Fraction f2(1, 1u, 2u);
            Fraction f3 = f1.add(f2);
            QFAIL("OverflowException is not thrown !");
        }
        catch(OverflowException){
            error = true;
        }
        QCOMPARE(error,true);
    }

    void testFractionAddOperator()
    {
        Fraction f1(-1,2u,5u);
        Fraction f2(1,3u,7u);

        Fraction f3 = f1 + f2;

        QCOMPARE( f3.sign(), 1 );
        QCOMPARE( f3.numerator(), -(2u*7u)+3u*5u );
        QCOMPARE( f3.denominator(), 5u*7u );
    }

    void testFractionSubtract()
    {
        Fraction f1(1,2u,5u);
        Fraction f2(1,3u,7u);

        Fraction f3 = f1.subtract(f2);

        QCOMPARE( f3.sign(), -1 );
        QCOMPARE( f3.numerator(), (3u*5u)-(2u*7u) );
        QCOMPARE( f3.denominator(), 5u*7u );
    }

    void testFractionSubtractOperator()
    {
        Fraction f1(1,2u,5u);
        Fraction f2(1,3u,7u);

        Fraction f3 = f1 - f2;

        QCOMPARE( f3.sign(), -1 );
        QCOMPARE( f3.numerator(), (3u*5u)-(2u*7u) );
        QCOMPARE( f3.denominator(), 5u*7u );
    }

    void testFractionDivide()
    {
        Fraction f1(1,2u,5u);
        Fraction f2(-1,3u,7u);
        Fraction f3 = f1.divide(f2);
        QCOMPARE( f3.sign(), -1 );
        QCOMPARE( f3.numerator(), 2u*7u );
        QCOMPARE( f3.denominator(), 5u*3u );
    }

    void testFractionDivideOperator()
    {
        Fraction f1(1,2u,5u);
        Fraction f2(-1,3u,7u);
        Fraction f3 = f1 / f2;
        QCOMPARE( f3.sign(), -1 );
        QCOMPARE( f3.numerator(), 2u*7u );
        QCOMPARE( f3.denominator(), 5u*3u );
    }

};

QTEST_APPLESS_MAIN(NumberLib3TestTest)

#include "tst_numberlib3qtesttest.moc"
