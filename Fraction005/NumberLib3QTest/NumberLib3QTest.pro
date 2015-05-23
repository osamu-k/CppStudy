#-------------------------------------------------
#
# Project created by QtCreator 2015-05-20T23:41:46
#
#-------------------------------------------------

QT       += testlib

QT       -= gui

TARGET = tst_numberlib3qtesttest
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += tst_numberlib3qtesttest.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../NumberLib3/release/ -lNumberLib3
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../NumberLib3/debug/ -lNumberLib3
else:unix: LIBS += -L$$OUT_PWD/../NumberLib3/ -lNumberLib3

INCLUDEPATH += $$PWD/../NumberLib3
DEPENDPATH += $$PWD/../NumberLib3

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../NumberLib3/release/libNumberLib3.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../NumberLib3/debug/libNumberLib3.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../NumberLib3/release/NumberLib3.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../NumberLib3/debug/NumberLib3.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../NumberLib3/libNumberLib3.a
