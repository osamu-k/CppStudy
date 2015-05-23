#-------------------------------------------------
#
# Project created by QtCreator 2015-05-17T23:22:34
#
#-------------------------------------------------

QT       -= core gui

TARGET = NumberLib
TEMPLATE = lib
CONFIG += staticlib

SOURCES += numberlib.c \
    fraction.c

HEADERS += numberlib.h \
    fraction.h
unix {
    target.path = /usr/lib
    INSTALLS += target
}
