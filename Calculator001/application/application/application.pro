#-------------------------------------------------
#
# Project created by QtCreator 2015-05-04T18:56:03
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = application
TEMPLATE = app


SOURCES += main.cpp\
        mainwidget.cpp

HEADERS  += mainwidget.h

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../product/product/release/ -lproduct
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../product/product/debug/ -lproduct
else:unix: LIBS += -L$$OUT_PWD/../../product/product/ -lproduct

INCLUDEPATH += $$PWD/../../product/product
DEPENDPATH += $$PWD/../../product/product

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../product/product/release/libproduct.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../product/product/debug/libproduct.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../product/product/release/product.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../product/product/debug/product.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../../product/product/libproduct.a
