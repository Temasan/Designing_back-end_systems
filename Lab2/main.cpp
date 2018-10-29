#include "widget.h"
#include <QApplication>
#include <dinner.h>
#include <QFile>
#include <enums.h>
/*vectorNames readNamesFromFile(){
    vectorNames names;
    QFile file(":/name_phylosophies.txt");
    if(file.open(QFile::ReadOnly | QFile::Text)){
        std::string bufStr = file.readLine().toStdString();
        std::vector<std::string> results;

        boost::split(results, bufStr, [](char c){return c == ', ';});
        for(std::string i: results){
            names.push_back(QString::fromUtf8(i.c_str()));
        }
    }
    file.close();
    return names;
}*/

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
