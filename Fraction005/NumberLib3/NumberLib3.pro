#-------------------------------------------------
#
# Project created by QtCreator 2015-05-20T23:38:44
#
#-------------------------------------------------

QT       -= core gui

TARGET = NumberLib3
TEMPLATE = lib
CONFIG += staticlib

SOURCES += numberlib3.cpp \
    fraction.cpp

HEADERS += numberlib3.h \
    fraction.h
unix {
    target.path = /usr/lib
    INSTALLS += target
}
