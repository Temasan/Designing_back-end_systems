#-------------------------------------------------
#
# Project created by QtCreator 2018-10-29T22:37:13
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Lab2
TEMPLATE = app
CONFIG += debug


SOURCES += main.cpp\
    dinner.cpp \
    philosopher.cpp \
#    stick.cpp \
    widget.cpp

HEADERS  += dinner.h \
    enums.h \
#    stick.h \
    philosopher.h \
    widget.h

FORMS    += widget.ui

