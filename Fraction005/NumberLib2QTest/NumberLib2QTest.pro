#-------------------------------------------------
#
# Project created by QtCreator 2015-05-20T22:50:45
#
#-------------------------------------------------

QT       += testlib

QT       -= gui

TARGET = tst_numberlib2qtesttest
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += tst_numberlib2qtesttest.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../NumberLib2/release/ -lNumberLib2
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../NumberLib2/debug/ -lNumberLib2
else:unix: LIBS += -L$$OUT_PWD/../NumberLib2/ -lNumberLib2

INCLUDEPATH += $$PWD/../NumberLib2
DEPENDPATH += $$PWD/../NumberLib2

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../NumberLib2/release/libNumberLib2.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../NumberLib2/debug/libNumberLib2.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../NumberLib2/release/NumberLib2.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../NumberLib2/debug/NumberLib2.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../NumberLib2/libNumberLib2.a
