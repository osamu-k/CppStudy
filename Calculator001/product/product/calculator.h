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

    enum state m_state;
    QString m_currentData;
    func_ptr m_operation;
};

#endif // CALCULATOR_H
