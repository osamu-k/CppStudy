#include <QLineEdit>
#include <QString>
#include <QtTest>
#include <QCoreApplication>
#include <QWidget>

#include "calculator.h"

class TestTest : public QObject
{
    Q_OBJECT

public:
    TestTest();

private Q_SLOTS:
    void initTestCase();
    void cleanupTestCase();
    void init()
    {
        calculator = new Calculator;
        calculator->show();
    }
    void cleanup()
    {
        if(calculator){
            delete calculator;
            calculator = 0;
        }
    }

    void testInputNumber();
    void testInputDecimalNumber();
    void testInputNumberPlus();
    void testInputNumberPlusNumber();
    void testInputNumberPlusNumberEq();
    void testInputNumberMinusNumberEq();
    void testInputNumberMultiplyNumberEq();
    void testInputNumberDivideNumberEq();
    void testInputDecimalPlusDecimalEq();
    void testInputDecimalMinusDecimalEq();
    void testInputDecimalMultiplyDecimalEq();
    void testInputDecimalDivideDecimalEq();
    void testInputSign();
    void testInputSignSign();
    void testInputNumberSign();
    void testInputNumberSignSign();
    void testInputDot();
    void testInputSignDot();
    void testInputSignNumberPlusSignNumberEq();
    void testInputNumberPlusNumberPlusNumberEq();

private:
    void clickButton(QString name);
    void clickString( const char *s );
    void assertInput( QString text );
    void assertDisplay( QString text );

    Calculator *calculator;
};

TestTest::TestTest()
{
}

void TestTest::initTestCase()
{
}

void TestTest::cleanupTestCase()
{
}

void TestTest::testInputNumber()
{
    clickString("123");
    assertInput("123");
    assertDisplay("");
}

void TestTest::testInputDecimalNumber()
{
    clickString("123.45");
    assertInput("123.45");
    assertDisplay("");
}

void TestTest::testInputNumberPlus()
{
    clickString("123+");
    assertInput("");
    assertDisplay("123 +");
}

void TestTest::testInputNumberPlusNumber()
{
    clickString("123+45");
    assertInput("45");
    assertDisplay("123 +");
}

void TestTest::testInputNumberPlusNumberEq()
{
    clickString("123+45=");
    assertInput("");
    assertDisplay(QString::number(123+45));
}

void TestTest::testInputNumberMinusNumberEq()
{
    clickString("123-45=");
    assertInput("");
    assertDisplay(QString::number(123-45));
}

void TestTest::testInputNumberMultiplyNumberEq()
{
    clickString("123*45=");
    assertInput("");
    assertDisplay(QString::number(123*45));
}

void TestTest::testInputNumberDivideNumberEq()
{
    clickString("123*45=");
    assertInput("");
    assertDisplay(QString::number(123.0*45.0));
}

void TestTest::testInputDecimalPlusDecimalEq()
{
    clickString("123.45+67.890=");
    assertInput("");
    assertDisplay(QString::number(123.45+67.890));
}

void TestTest::testInputDecimalMinusDecimalEq()
{
    clickString("123.45-67.890=");
    assertInput("");
    assertDisplay(QString::number(123.45-67.890));
}

void TestTest::testInputDecimalMultiplyDecimalEq()
{
    clickString("123.45*67.890=");
    assertInput("");
    assertDisplay(QString::number(123.45*67.890));
}

void TestTest::testInputDecimalDivideDecimalEq()
{
    clickString("123.45/67.890=");
    assertInput("");
    assertDisplay(QString::number(123.45/67.890));
}

void TestTest::testInputSign()
{
    clickString("S");
    assertInput("-");
    assertDisplay("");
}

void TestTest::testInputSignSign()
{
    clickString("SS");
    assertInput("");
    assertDisplay("");
}

void TestTest::testInputNumberSign()
{
    clickString("1S");
    assertInput("-1");
    assertDisplay("");
}

void TestTest::testInputNumberSignSign()
{
    clickString("1SS");
    assertInput("1");
    assertDisplay("");
}

void TestTest::testInputDot()
{
    clickString(".");
    assertInput("0.");
    assertDisplay("");
}

void TestTest::testInputSignDot()
{
    clickString("S.");
    assertInput("-0.");
    assertDisplay("");
}

void TestTest::testInputSignNumberPlusSignNumberEq()
{
    clickString("123S+45S=");
    assertInput("");
    assertDisplay(QString::number((-123)+(-45)));
}

void TestTest::testInputNumberPlusNumberPlusNumberEq()
{
    clickString("123+45+678=");
    assertInput("");
    assertDisplay(QString::number(123+45+678));
}

void TestTest::clickButton(QString name)
{
    QWidget *button1 = calculator->findChild<QWidget*>(name);
    QVERIFY2(button1 != 0, QString("could not find \"%1\".").arg(name).toLatin1().constData() );
    //QTest::qWait( 200 );
    QTest::mousePress(button1,Qt::LeftButton);
    //QTest::qWait( 200 );
    QTest::mouseRelease(button1,Qt::LeftButton);
    //QTest::qWait( 200 );
}

void TestTest::clickString( const char *s )
{
    QString objectName;
    for( const char *p = s; *p != '\0'; p++ ){
        switch(*p){
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
            clickButton( QString("button%1").arg(*p) );
            break;
        case '.':
            clickButton( QString("buttonDot") );
            break;
        case 'S':
            clickButton( QString("buttonSign") );
            break;
        case '+':
            clickButton( QString("buttonAdd") );
            break;
        case '-':
            clickButton( QString("buttonSub") );
            break;
        case '*':
            clickButton( QString("buttonMul") );
            break;
        case '/':
            clickButton( QString("buttonDiv") );
            break;
        case '=':
            clickButton( QString("buttonEqual") );
            break;
        case 'A':
            clickButton( QString("buttonAllClear") );
            break;
        case 'C':
            clickButton( QString("buttonClear") );
            break;
        default:
            break;
        }
        if( !objectName.isEmpty() ){
            clickButton( objectName );
        }
    }
}

void TestTest::assertInput( QString text )
{
    QLineEdit *lineInput = calculator->findChild<QLineEdit*>("lineInput");
    QCOMPARE( lineInput->text(), QString(text) );
}

void TestTest::assertDisplay( QString text )
{
    QLineEdit *lineDisplay = calculator->findChild<QLineEdit*>("lineDisplay");
    QCOMPARE( lineDisplay->text(), QString(text) );
}

QTEST_MAIN(TestTest)

#include "tst_testtest.moc"
