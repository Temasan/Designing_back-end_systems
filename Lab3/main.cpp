#include "widget.h"
#include <QApplication>
#include <dinner.h>
#include <enums.h>

/*!
 * Задача - консенсус с использованием Phase king (Король состояния)
 * В определенный такт времени выбирается лидер, который должен опросить все узлы и приянть из данные.
 * Далее, опросив все узлы, король определяет по времени, какие данные были самые первые, и утерждает их для всех узлов.
 * - Опрос данных о философах на стороне столовой при вызове их из клиентов
 * - Создание класса события, который хранит номер палки, её состояние и время создания
 * - Философу-королю после опроса следует выбраться самые первые данные и после установления консенсуса, удалить логи из других философов
 * - Организовать список-лог событий на стороне каждого философа
 */
/*!
 * \todo
 * для столовой переделать функцию-вызов, опрвщивающую всех философов
 * для философов добавить список логов событий, добавить метод очистки логов
 */

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    qRegisterMetaType<EatingState>("EatingState");
    qRegisterMetaType<PushingStickEnum>("PushingStickEnum");
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
