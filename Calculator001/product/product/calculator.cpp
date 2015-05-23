#include "calculator.h"

#include <QDebug>
#include <QGridLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>

#include <algorithm>
using namespace std;

Calculator::Calculator(QWidget *parent)
    : QWidget(parent)
    , m_state(STATE_NUM1_WAITING)
{
    QVBoxLayout *vboxLayout = new QVBoxLayout;

    QLineEdit *lineDisplay = createLineEdit("lineDisplay");
    vboxLayout->addWidget(lineDisplay);

    QLineEdit *lineInput = createLineEdit("lineInput");
    vboxLayout->addWidget(lineInput);

    QPushButton *button0 = createNumberButton( 0 );
    QPushButton *button1 = createNumberButton( 1 );
    QPushButton *button2 = createNumberButton( 2 );
    QPushButton *button3 = createNumberButton( 3 );
    QPushButton *button4 = createNumberButton( 4 );
    QPushButton *button5 = createNumberButton( 5 );
    QPushButton *button6 = createNumberButton( 6 );
    QPushButton *button7 = createNumberButton( 7 );
    QPushButton *button8 = createNumberButton( 8 );
    QPushButton *button9 = createNumberButton( 9 );

    QPushButton *buttonDot = createDotButton();
    QPushButton *buttonSign = createSignButton();

    QPushButton *buttonAdd = createAddButton();
    QPushButton *buttonSub = createSubButton();
    QPushButton *buttonMul = createMulButton();
    QPushButton *buttonDiv = createDivButton();

    QPushButton *buttonEq = createEqualButton();

    QPushButton *buttonAC = createAllClearButton();
    QPushButton *buttonC = createClearButton();

    QGridLayout *gridLayout = new QGridLayout;

    gridLayout->addWidget(buttonAC  ,0,0);
    gridLayout->addWidget(buttonC   ,0,1);
    gridLayout->addWidget(buttonSign,0,2);
    gridLayout->addWidget(buttonDiv ,0,3);

    gridLayout->addWidget(button7   ,1,0);
    gridLayout->addWidget(button8   ,1,1);
    gridLayout->addWidget(button9   ,1,2);
    gridLayout->addWidget(buttonMul ,1,3);

    gridLayout->addWidget(button4   ,2,0);
    gridLayout->addWidget(button5   ,2,1);
    gridLayout->addWidget(button6   ,2,2);
    gridLayout->addWidget(buttonSub ,2,3);

    gridLayout->addWidget(button1   ,3,0);
    gridLayout->addWidget(button2   ,3,1);
    gridLayout->addWidget(button3   ,3,2);
    gridLayout->addWidget(buttonAdd ,3,3);

    gridLayout->addWidget(button0   ,4,0,1,2);
    gridLayout->addWidget(buttonDot ,4,2);
    gridLayout->addWidget(buttonDot ,4,2);
    gridLayout->addWidget(buttonEq  ,4,3);

    vboxLayout->addLayout(gridLayout);
    setLayout(vboxLayout);

    disableIrrelevantButtons();
}

Calculator::~Calculator()
{
}

QLineEdit *Calculator::createLineDisplay()
{
    return createLineEdit("lineDisplay");
}

QLineEdit *Calculator::createLineInput()
{
    return createLineEdit("lineInput");
}

QLineEdit *Calculator::createLineEdit( QString objectName )
{
    QLineEdit *lineEdit = new QLineEdit;
    lineEdit->setObjectName(objectName);
    lineEdit->setReadOnly(true);
    lineEdit->setAlignment(Qt::AlignRight);
    return lineEdit;
}

QPushButton *Calculator::createNumberButton( int i )
{
    QString label = QString::number(i);
    QString objectName = QString("button%1").arg(i);
    QPushButton *button = new QPushButton(label);
    button->setObjectName(objectName);
    connect( button, &QPushButton::clicked,
             [=](){ numberButtonClicked(label); } );
    return button;
}

QPushButton *Calculator::createDotButton()
{
    QString label(".");
    QString objectName( "buttonDot" );
    QPushButton *button = new QPushButton(label);
    button->setObjectName(objectName);
    connect( button, &QPushButton::clicked, this, &Calculator::dotButtonClicked );
    return button;
}

QPushButton *Calculator::createSignButton()
{
    QString label("+/-");
    QString objectName( "buttonSign" );
    QPushButton *button = new QPushButton(label);
    button->setObjectName(objectName);
    connect( button, &QPushButton::clicked, this, &Calculator::signButtonClicked );
    return button;
}

QPushButton *Calculator::createAddButton()
{
    return createOperatorButton( "+", "buttonAdd", [](double x, double y)->double{ return x + y; });
}

QPushButton *Calculator::createSubButton()
{
    return createOperatorButton( "-", "buttonSub", [](double x, double y)->double{ return x - y; });
}

QPushButton *Calculator::createMulButton()
{
    return createOperatorButton( "×", "buttonMul", [](double x, double y)->double{ return x * y; });
}

QPushButton *Calculator::createDivButton()
{
    return createOperatorButton( "÷", "buttonDiv", [](double x, double y)->double{ return x / y; });
}

QPushButton *Calculator::createOperatorButton( QString label, QString objectName, double (*func)(double, double) )
{
    QPushButton *button = new QPushButton(label);
    button->setObjectName(objectName);
    connect( button, &QPushButton::clicked, [=](){operatorButtonClicked(label,func);} );
    return button;
}
QPushButton *Calculator::createEqualButton()
{
    QString label("=");
    QString objectName( "buttonEqual" );
    QPushButton *button = new QPushButton(label);
    button->setObjectName(objectName);
    connect( button, &QPushButton::clicked, this, &Calculator::equalButtonClicked );
    return button;
}

QPushButton *Calculator::createAllClearButton()
{
    QString label("AC");
    QString objectName( "buttonAllClear" );
    QPushButton *button = new QPushButton(label);
    button->setObjectName(objectName);
    connect( button, &QPushButton::clicked, this, &Calculator::allClearButtonClicked );
    return button;
}

QPushButton *Calculator::createClearButton()
{
    QString label("C");
    QString objectName( "buttonClear" );
    QPushButton *button = new QPushButton(label);
    button->setObjectName(objectName);
    connect( button, &QPushButton::clicked, this, &Calculator::clearButtonClicked );
    return button;
}

QLineEdit *Calculator::getLineDisplay()
{
    return findChild<QLineEdit *>( "lineDisplay" );
}

QLineEdit *Calculator::getLineInput()
{
    return findChild<QLineEdit *>( "lineInput" );
}

QPushButton *Calculator::getNumberButton( int i )
{
    QString objectName = QString("button%1").arg(i);
    return findChild<QPushButton *>( objectName );
}

QPushButton *Calculator::getDotButton()
{
    return findChild<QPushButton *>( "buttonDot" );
}

QPushButton *Calculator::getSignButton()
{
    return findChild<QPushButton *>( "buttonSign" );
}

QPushButton *Calculator::getAddButton()
{
    return findChild<QPushButton *>( "buttonAdd" );
}

QPushButton *Calculator::getSubButton()
{
    return findChild<QPushButton *>( "buttonSub" );
}

QPushButton *Calculator::getMulButton()
{
    return findChild<QPushButton *>( "buttonMul" );
}

QPushButton *Calculator::getDivButton()
{
    return findChild<QPushButton *>( "buttonDiv" );
}

QPushButton *Calculator::getEqualButton()
{
    return findChild<QPushButton *>( "buttonEqual" );
}

QPushButton *Calculator::getAllClearButton()
{
    return findChild<QPushButton *>( "buttonAllClear" );
}

QPushButton *Calculator::getClearButton()
{
    return findChild<QPushButton *>( "buttonClear" );
}

void Calculator::disableIrrelevantButtons()
{
    QPushButton *buttonDot = getDotButton();
    QPushButton *buttonAdd = getAddButton();
    QPushButton *buttonSub = getSubButton();
    QPushButton *buttonMul = getMulButton();
    QPushButton *buttonDiv = getDivButton();
    QPushButton *buttonEq  = getEqualButton();

    buttonDot->setDisabled(false);
    buttonAdd->setDisabled(false);
    buttonSub->setDisabled(false);
    buttonMul->setDisabled(false);
    buttonDiv->setDisabled(false);
    buttonEq ->setDisabled(false);


    switch(m_state){
    case STATE_NUM1_WAITING:
        buttonAdd->setDisabled(true);
        buttonSub->setDisabled(true);
        buttonMul->setDisabled(true);
        buttonDiv->setDisabled(true);
        buttonEq ->setDisabled(true);
        return;
    case STATE_NUM1_INTEGER_PART:
        buttonEq ->setDisabled(true);
        return;
    case STATE_NUM1_DECIMAL_PART:
        buttonDot->setDisabled(true);
        buttonEq ->setDisabled(true);
        return;
    case STATE_NUM2_WAITING:
        buttonAdd->setDisabled(true);
        buttonSub->setDisabled(true);
        buttonMul->setDisabled(true);
        buttonDiv->setDisabled(true);
        buttonEq ->setDisabled(true);
        return;
    case STATE_NUM2_INTEGER_PART:
        return;
    case STATE_NUM2_DECIMAL_PART:
        buttonDot->setDisabled(true);
        return;
    case STATE_SHOW_RESULT:
        buttonEq ->setDisabled(true);
        return;
    default:
        return;
    }
}

void Calculator::numberButtonClicked( QString digit )
{
    getLineInput()->setText( getLineInput()->text() + digit );

    switch(m_state){
    case STATE_NUM1_WAITING:
        m_state = STATE_NUM1_INTEGER_PART;
        break;
    case STATE_NUM1_INTEGER_PART:
    case STATE_NUM1_DECIMAL_PART:
        // No state change
        break;
    case STATE_NUM2_WAITING:
        m_state = STATE_NUM2_INTEGER_PART;
        break;
    case STATE_NUM2_INTEGER_PART:
    case STATE_NUM2_DECIMAL_PART:
        // No state change
        break;
    case STATE_SHOW_RESULT:
        m_state = STATE_NUM1_INTEGER_PART;
        break;
    default:
        return;
    }
    disableIrrelevantButtons();
}

void Calculator::dotButtonClicked()
{
    QString instr = getLineInput()->text();

    switch(m_state){
    case STATE_NUM1_WAITING:
        instr += "0.";
        m_state = STATE_NUM1_DECIMAL_PART;
        break;
    case STATE_NUM1_INTEGER_PART:
        instr += ".";
        m_state = STATE_NUM1_DECIMAL_PART;
        break;
    case STATE_NUM1_DECIMAL_PART:
        // Nothing to do
        return;
    case STATE_NUM2_WAITING:
        instr += "0.";
        m_state = STATE_NUM2_DECIMAL_PART;
        break;
    case STATE_NUM2_INTEGER_PART:
        instr += ".";
        m_state = STATE_NUM2_DECIMAL_PART;
        break;
    case STATE_NUM2_DECIMAL_PART:
        // Nothing to do
        return;
    case STATE_SHOW_RESULT:
        instr += "0.";
        m_state = STATE_NUM1_DECIMAL_PART;
        break;
    default:
        return;
    }

    getLineInput()->setText( instr );
    disableIrrelevantButtons();
}

void Calculator::signButtonClicked()
{
    QString instr = getLineInput()->text();
    if( (instr.size()) > 0 && (instr[0] == '-') ){
        instr = instr.right( instr.size() - 1 );
    }
    else{
        instr = "-" + instr;
    }
    getLineInput()->setText( instr );
}

void Calculator::operatorButtonClicked(QString label, func_ptr func)
{
    switch(m_state){
    case STATE_NUM1_WAITING:
        // Nothing to do
        return;
    case STATE_NUM1_INTEGER_PART:
    case STATE_NUM1_DECIMAL_PART:
        m_currentData = getLineInput()->text();
        break;
    case STATE_NUM2_WAITING:
        // Nothing to do
        return;
    case STATE_NUM2_INTEGER_PART:
    case STATE_NUM2_DECIMAL_PART:
    {
        double answer = m_operation( m_currentData.toDouble(), getLineInput()->text().toDouble() );
        m_currentData = QString::number(answer);
        break;
    }
    case STATE_SHOW_RESULT:
        m_currentData = getLineDisplay()->text();
        break;
    default:
        return;
    }
    getLineDisplay()->setText( m_currentData + " " + label );
    getLineInput()->clear();
    m_operation = func;
    m_state = STATE_NUM2_WAITING;
    disableIrrelevantButtons();
}

void Calculator::equalButtonClicked()
{
    switch(m_state){
    case STATE_NUM1_WAITING:
    case STATE_NUM1_INTEGER_PART:
    case STATE_NUM1_DECIMAL_PART:
    case STATE_NUM2_WAITING:
        // Nothing to do
        return;
    case STATE_NUM2_INTEGER_PART:
    case STATE_NUM2_DECIMAL_PART:
    {
        double answer = m_operation( m_currentData.toDouble(), getLineInput()->text().toDouble() );
        getLineDisplay()->setText( QString::number(answer) );
        getLineInput()->clear();
        m_operation = 0;
        m_state = STATE_SHOW_RESULT;
        break;
    }
    case STATE_SHOW_RESULT:
        // Nothing to do
        return;
    default:
        return;
    }
    disableIrrelevantButtons();
}

void Calculator::allClearButtonClicked()
{
    getLineDisplay()->clear();
    getLineInput()->clear();
    m_currentData.clear();
    m_operation = 0;
    m_state = STATE_NUM1_WAITING;
    disableIrrelevantButtons();
}

void Calculator::clearButtonClicked()
{
    switch(m_state){
    case STATE_NUM1_WAITING:
        // Nothing to do.
        return;
    case STATE_NUM1_INTEGER_PART:
    case STATE_NUM1_DECIMAL_PART:
        getLineInput()->clear();
        m_state = STATE_NUM1_WAITING;
        break;
    case STATE_NUM2_WAITING:
        // Nothing to do.
        return;
    case STATE_NUM2_INTEGER_PART:
    case STATE_NUM2_DECIMAL_PART:
        getLineInput()->clear();
        m_state = STATE_NUM2_WAITING;
        break;
    case STATE_SHOW_RESULT:
        // Nothing to do.
        return;
    default:
        return;
    }
    disableIrrelevantButtons();
}
