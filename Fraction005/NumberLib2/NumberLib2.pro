#-------------------------------------------------
#
# Project created by QtCreator 2015-05-20T22:47:40
#
#-------------------------------------------------

QT       -= core gui

TARGET = NumberLib2
TEMPLATE = lib
CONFIG += staticlib

SOURCES += \
    numberlib2.c \
    fraction2.c

HEADERS += numberlib2.h \
    fraction2.h
unix {
    target.path = /usr/lib
    INSTALLS += target
}
