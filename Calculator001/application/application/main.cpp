#include <QApplication>

#include "mainwidget.h"
#include "calculator.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    MainWidget w;
//    w.show();
    Calculator calc;
    calc.show();

    return a.exec();
}
