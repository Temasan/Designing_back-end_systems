#include "philosopher.h"
#include <QDebug>
#include <chrono>
#include <thread>

Philosopher::Philosopher(std::pair<int, int> pairSticsNumber, QThread *parent):
    QThread(parent)
{
    m_firstNumberStik.store(pairSticsNumber.first);
    m_secondNumberStik.store(pairSticsNumber.second);

    //m_pauseMutex.lock();
   // m_pairSticks.first = stickOne;
   // m_pairSticks.second = stickTwo;
    //m_pauseMutex = std::move(ptrMutex);
//    m_timer = new QTimer(this);
//    m_timer->setInterval(1000);
    //QObject::connect(m_timer, SIGNAL(timeout()), this, SLOT(tickEat()));
}

void Philosopher::run(/*std::pair<ptrStick, ptrStick> &pairSticks*/){
    qDebug() << "I am lock " << QString::number(m_number);
    m_started = true;
    //m_pauseMutex.lock();
    m_pauseMutex.lock();
    qDebug() << "I am unlock " << QString::number(m_number);

    qDebug() << "Пробую захватить " << QString::number(m_number) << " " << QString::number(staticMutexNamesspace::stiks[m_firstNumberStik.load()]->getNumberStick())
             << " " << QString::number(staticMutexNamesspace::stiks[m_secondNumberStik.load()]->getNumberStick());

    while(!pushTwoStick()){};
    qDebug() << "I am start eating " << QString::number(m_number);
    m_eatingState = Eateing;
//    m_timer->start();
    tickEat();
}

void Philosopher::tickEat(/*std::pair<ptrStick, ptrStick> &pairSticks*/){
    while(m_nowTime!=m_eatingTime){
        std::this_thread::sleep_for (std::chrono::seconds(1));
        m_nowTime++;
        if(m_nowTime == m_eatingTime){
    //        m_timer->stop();
            m_eatingState = FinishEateing;
            qDebug() << "I am finish eating " << QString::number(m_number);
            staticMutexNamesspace::stiks[m_firstNumberStik.load()]->unlock();
            staticMutexNamesspace::stiks[m_secondNumberStik.load()]->unlock();

            //pairSticks.first->unLock();
            //pairSticks.second->unLock();
        }
        eating(m_nowTime, m_number, m_eatingState);
    }
}

bool Philosopher::pushTwoStick(/*std::pair<ptrStick, ptrStick> &pairSticks*/){
    /*
    qDebug() << "Пробую захватить " << QString::number(m_number) << " " << QString::number(m_firstNumberStik.load())
             << " " << QString::number(m_secondNumberStik.load());*/
    if(staticMutexNamesspace::stiks[m_firstNumberStik.load()]->tryLock()){
        if(staticMutexNamesspace::stiks[m_secondNumberStik.load()]->tryLock()){
            return true;
        }
        else{
            staticMutexNamesspace::stiks[m_firstNumberStik.load()]->unlock();
        }
    }
    return false;
}

bool Philosopher::getStarted() const
{
    return m_started;
}

int Philosopher::getNumber() const
{
    return m_number;
}

void Philosopher::setNumber(int number)
{
    m_number = number;
}


