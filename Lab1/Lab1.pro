#-------------------------------------------------
#
# Project created by QtCreator 2018-10-08T18:50:20
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Lab1
TEMPLATE = app


SOURCES += main.cpp\
#        widget.cpp \
    philosopher.cpp \
    stick.cpp \
    dinner.cpp

HEADERS  += philosopher.h \
    stick.h \
    dinner.h


RESOURCES += \
    qml.qrc

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../FrontEnd/release/ -lFrontEnd
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../FrontEnd/debug/ -lFrontEnd
else:unix:!macx: LIBS += -L$$OUT_PWD/../FrontEnd/ -lFrontEnd

INCLUDEPATH += $$PWD/../FrontEnd
DEPENDPATH += $$PWD/../FrontEnd
