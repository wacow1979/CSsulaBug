#-------------------------------------------------
#
# Project created by QtCreator 2012-03-12T22:48:54
#
#-------------------------------------------------

QT       += core gui network sql

TARGET = CSsulaBug
TEMPLATE = app


SOURCES += main.cpp \
    sfupdater.cpp \
    networkaccessor.cpp \
    comicinfo.cpp \
    sfcoverupdater.cpp \
    mainwindow.cpp \
    form.cpp \
    sfdownloadpreparer.cpp \
    downloadcontroller.cpp

HEADERS  += \
    sfupdater.h \
    networkaccessor.h \
    comicinfo.h \
    sfcoverupdater.h \
    mainwindow.h \
    form.h \
    sfdownloadpreparer.h \
    downloadcontroller.h

FORMS    += \
    mainwindow.ui \
    form.ui
