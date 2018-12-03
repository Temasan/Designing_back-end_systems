#include "widget.h"
#include <QApplication>
#include <dinner.h>
#include <QFile>
#include <enums.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    qRegisterMetaType<EatingState>("EatingState");
    qRegisterMetaType<std::pair<int,int>>("std::pair<int,int>");
    Dinner d;
    Widget w;
    w.show();
    QObject::connect(w.startButton(), SIGNAL(clicked(bool)),&d,SLOT(start(bool)));
    QObject::connect(w.spinBox(), SIGNAL(valueChanged(int)),&d,SLOT(setNumberPhylosophers(int)));
    QObject::connect(&d, SIGNAL(getPropertiesToWidget(QString,int,EatingState,std::pair<int, int>)),
                     &w,SLOT(onDataChange(QString,int,EatingState,std::pair<int, int>)));

    QObject::connect(&d, SIGNAL(putStick(int,bool,int)),
                     &w,SLOT(onPutStick(int,bool,int)));
    return a.exec();
}
