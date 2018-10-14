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
        widget.cpp \
    philosopher.cpp \
    stick.cpp \
    dinner.cpp

HEADERS  += widget.h \
    philosopher.h \
    stick.h \
    dinner.h \
    enums.h

FORMS    += widget.ui

RESOURCES += \
    qml.qrc
