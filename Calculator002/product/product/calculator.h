#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QMap>
#include <QPushButton>
#include <QWidget>

#include <functional>

class QGridLayout;
class QLineEdit;
class QPushButton;

class Calculator : public QWidget
{
    Q_OBJECT

public:
    explicit Calculator(QWidget *parent = 0);
    ~Calculator();

signals:

public slots:

private:
    typedef double(*func_ptr)(double, double);

private slots:
    void numberButtonClicked(QString digit);
    void dotButtonClicked();
    void signButtonClicked();
    void operatorButtonClicked(QString label, func_ptr func);
    void equalButtonClicked();
    void allClearButtonClicked();
    void clearButtonClicked();

private:
    QLineEdit *createLineDisplay();
    QLineEdit *createLineInput();
    QLineEdit *createLineEdit(QString objectName);

    QPushButton *createNumberButton( int i );
    QPushButton *createDotButton();
    QPushButton *createSignButton();
    QPushButton *createAddButton();
    QPushButton *createSubButton();
    QPushButton *createMulButton();
    QPushButton *createDivButton();
    QPushButton *createOperatorButton( QString label, QString objectName, func_ptr func );
    QPushButton *createEqualButton();
    QPushButton *createAllClearButton();
    QPushButton *createClearButton();

    QLineEdit *getLineDisplay();
    QLineEdit *getLineInput();

    QPushButton *getNumberButton( int i );
    QPushButton *getDotButton();
    QPushButton *getSignButton();
    QPushButton *getAddButton();
    QPushButton *getSubButton();
    QPushButton *getMulButton();
    QPushButton *getDivButton();
    QPushButton *getEqualButton();
    QPushButton *getAllClearButton();
    QPushButton *getClearButton();

    void disableIrrelevantButtons();

    enum state{
        STATE_NUM1_WAITING,
        STATE_NUM1_INTEGER_PART,
        STATE_NUM1_DECIMAL_PART,
        STATE_NUM2_WAITING,
        STATE_NUM2_INTEGER_PART,
        STATE_NUM2_DECIMAL_PART,
        STATE_SHOW_RESULT
    };

//    enum state m_state;
    QString m_currentData;
    func_ptr m_operation;

    class State
    {
    public:
        State(Calculator *calculator, QString name);
        virtual ~State();
        virtual void disableIrrelevantButtons();
        virtual void numberButtonClicked(QString digit);
        virtual void dotButtonClicked();
        virtual void signButtonClicked();
        virtual void operatorButtonClicked(QString label, func_ptr func);
        virtual void equalButtonClicked();
        virtual void allClearButtonClicked();
        virtual void clearButtonClicked();
        QString name() { return m_name; }
    protected:
        void setState( State *state );
        Calculator *m_calculator;
        QString m_name;
    };
    class StateNum1Waiting : public State
    {
    public:
        StateNum1Waiting(Calculator *calculator);
        virtual ~StateNum1Waiting();
        virtual void disableIrrelevantButtons();
        virtual void numberButtonClicked(QString digit);
        virtual void dotButtonClicked();
//        virtual void signButtonClicked();
//        virtual void operatorButtonClicked(QString label, func_ptr func);
//        virtual void equalButtonClicked();
        virtual void allClearButtonClicked();
        virtual void clearButtonClicked();
    };
    class StateNum1IntegerPart : public State
    {
    public:
        StateNum1IntegerPart(Calculator *calculator);
        virtual ~StateNum1IntegerPart();
        virtual void disableIrrelevantButtons();
        virtual void numberButtonClicked(QString digit);
        virtual void dotButtonClicked();
//        virtual void signButtonClicked();
        virtual void operatorButtonClicked(QString label, func_ptr func);
//        virtual void equalButtonClicked();
        virtual void allClearButtonClicked();
        virtual void clearButtonClicked();
    };
    class StateNum1DecimalPart : public State
    {
    public:
        StateNum1DecimalPart(Calculator *calculator);
        virtual ~StateNum1DecimalPart();
        virtual void disableIrrelevantButtons();
        virtual void numberButtonClicked(QString digit);
        virtual void dotButtonClicked();
//        virtual void signButtonClicked();
        virtual void operatorButtonClicked(QString label, func_ptr func);
//        virtual void equalButtonClicked();
        virtual void allClearButtonClicked();
        virtual void clearButtonClicked();
    };
    class StateNum2Waiting : public State
    {
    public:
        StateNum2Waiting(Calculator *calculator);
        virtual ~StateNum2Waiting();
        virtual void disableIrrelevantButtons();
        virtual void numberButtonClicked(QString digit);
        virtual void dotButtonClicked();
//        virtual void signButtonClicked();
//        virtual void operatorButtonClicked(QString label, func_ptr func);
//        virtual void equalButtonClicked();
        virtual void allClearButtonClicked();
        virtual void clearButtonClicked();
    };
    class StateNum2IntegerPart : public State
    {
    public:
        StateNum2IntegerPart(Calculator *calculator);
        virtual ~StateNum2IntegerPart();
        virtual void disableIrrelevantButtons();
        virtual void numberButtonClicked(QString digit);
        virtual void dotButtonClicked();
//        virtual void signButtonClicked();
        virtual void operatorButtonClicked(QString label, func_ptr func);
        virtual void equalButtonClicked();
        virtual void allClearButtonClicked();
        virtual void clearButtonClicked();
    };
    class StateNum2DecimalPart : public State
    {
    public:
        StateNum2DecimalPart(Calculator *calculator);
        virtual ~StateNum2DecimalPart();
        virtual void disableIrrelevantButtons();
        virtual void numberButtonClicked(QString digit);
        virtual void dotButtonClicked();
//        virtual void signButtonClicked();
        virtual void operatorButtonClicked(QString label, func_ptr func);
        virtual void equalButtonClicked();
        virtual void allClearButtonClicked();
        virtual void clearButtonClicked();
    };
    class StateShowResult : public State
    {
    public:
        StateShowResult(Calculator *calculator);
        virtual ~StateShowResult();
        virtual void disableIrrelevantButtons();
        virtual void numberButtonClicked(QString digit);
        virtual void dotButtonClicked();
//        virtual void signButtonClicked();
        virtual void operatorButtonClicked(QString label, func_ptr func);
//        virtual void equalButtonClicked();
        virtual void allClearButtonClicked();
        virtual void clearButtonClicked();
    };

    StateNum1Waiting     m_stateNum1Waiting;
    StateNum1IntegerPart m_stateNum1IntegerPart;
    StateNum1DecimalPart m_stateNum1DecimalPart;
    StateNum2Waiting     m_stateNum2Waiting;
    StateNum2IntegerPart m_stateNum2IntegerPart;
    StateNum2DecimalPart m_stateNum2DecimalPart;
    StateShowResult      m_stateShowResult;

    State *m_state;
};

#endif // CALCULATOR_H
