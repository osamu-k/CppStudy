#-------------------------------------------------
#
# Project created by QtCreator 2015-05-04T18:48:03
#
#-------------------------------------------------

QT       += widgets

TARGET = product
TEMPLATE = lib
CONFIG += staticlib

DEFINES += PRODUCT_LIBRARY

QMAKE_CXXFLAGS += -std=c++11 -stdlib=libc++

SOURCES += \
    calculator.cpp

HEADERS +=\
        product_global.h \
    calculator.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
