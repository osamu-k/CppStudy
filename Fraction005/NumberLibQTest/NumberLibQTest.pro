#-------------------------------------------------
#
# Project created by QtCreator 2015-05-17T23:46:36
#
#-------------------------------------------------

QT       += testlib

QT       -= gui

TARGET = tst_numberlibqtesttest
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += tst_numberlibqtesttest.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../NumberLib/release/ -lNumberLib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../NumberLib/debug/ -lNumberLib
else:unix: LIBS += -L$$OUT_PWD/../NumberLib/ -lNumberLib

INCLUDEPATH += $$PWD/../NumberLib
DEPENDPATH += $$PWD/../NumberLib

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../NumberLib/release/libNumberLib.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../NumberLib/debug/libNumberLib.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../NumberLib/release/NumberLib.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../NumberLib/debug/NumberLib.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../NumberLib/libNumberLib.a
