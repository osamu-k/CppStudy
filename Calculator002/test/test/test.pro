#-------------------------------------------------
#
# Project created by QtCreator 2015-05-04T19:03:42
#
#-------------------------------------------------

QT       += widgets testlib

TARGET = tst_testtest
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += tst_testtest.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"

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
