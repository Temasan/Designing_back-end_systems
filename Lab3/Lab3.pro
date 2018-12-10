
QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
CONFIG += C++11
TARGET = Lab2
TEMPLATE = app
SOURCES += \
    main.cpp \
    philosopher.cpp \
    dinner.cpp \
    datastickstatus.cpp

HEADERS += \
    philosopher.h \
    dinner.h \
    datastickstatus.h

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../FrontEnd/release/ -lFrontEnd
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../FrontEnd/debug/ -lFrontEnd
else:unix:!macx: LIBS += -L$$OUT_PWD/../FrontEnd/ -lFrontEnd

INCLUDEPATH += $$PWD/../FrontEnd
DEPENDPATH += $$PWD/../FrontEnd
