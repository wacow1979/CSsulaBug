#-------------------------------------------------
#
# Project created by QtCreator 2014-07-22T12:32:20
#
#-------------------------------------------------

QT += testlib network

TARGET = unittest
CONFIG += console testcase


SOURCES += \
    convertztest.cpp \
    main.cpp \
    stubcomicsitehandler.cpp \
    servicetest.cpp

HEADERS += \
    convertztest.h \
    stubcomicsitehandler.h \
    servicetest.h

INCLUDEPATH += $$PWD/../../core

win32-g++:CONFIG(debug, debug|release):{
    LIBS += -L$$OUT_PWD/../../core/debug -lcore
    PRE_TARGETDEPS += $$OUT_PWD/../../core/debug/libcore.a
}

win32-g++:CONFIG(release, debug|release):{
    LIBS += -L$$OUT_PWD/../../core/release -lcore
    PRE_TARGETDEPS += $$OUT_PWD/../../core/release/libcore.a
}

unix:CONFIG(release, debug|release){
    LIBS += -L$$OUT_PWD/../../core -lcore
    PRE_TARGETDEPS += $$OUT_PWD/../../core/libcore.a
}
