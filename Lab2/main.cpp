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

/*!
 * \todo Организация потоков, используя подхода акторов
 * Идея: каждый философ - актор, который кидает другим философам сообщения по типу: я возьму твою палочку, и если у того она свободна
 * то он её отдает. Когда он её отдаст, то у его палочки повяляется статус "взята". Также философы могут говорить соседям, что они
 * освободили их палочки. Следовательно, нужда в классах палочках полностью отпадает, ибо по дефолту все палочки философов отпущены.
 * - связать философов через сигнал-слот систему одну функцию с передачей сообщений
 * - удалить и отвязать класс палочек
 */

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    qRegisterMetaType<EatingState>("EatingState");
    qRegisterMetaType<Philosopher::PushingStickEnum>("PushingStickEnum");
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
