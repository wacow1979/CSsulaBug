#-------------------------------------------------
#
# Project created by QtCreator 2012-03-12T22:48:54
#
#-------------------------------------------------

TARGET = CSsulaBug
TEMPLATE = app
QT += quick

#macx {
#    ICON = $$PWD/icon.icns
#}
#win32 {
#    RC_FILE = CSsulaBug.rc
#}

SOURCES += \
    main.cpp

RESOURCES += \
    app_resource.qrc

INCLUDEPATH += $$PWD/../src

win32-g++:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../src/debug -lcssulabug