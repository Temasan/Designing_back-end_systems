QT += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

#TARGET = FrontEnd
TEMPLATE = lib

HEADERS += \
    widget.h \
    enums.h

SOURCES += \
    widget.cpp

FORMS += \
    widget.ui
