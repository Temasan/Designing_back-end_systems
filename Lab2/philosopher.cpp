#include "philosopher.h"
#include <QDebug>
#include <chrono>
#include <thread>

Philosopher::Philosopher(std::pair<int, int> pairSticsNumber, QThread *parent):
    QThread(parent)
{
    m_firstNumberStik.store(pairSticsNumber.first);
    m_secondNumberStik.store(pairSticsNumber.second);
}

void Philosopher::run(){
    //qDebug() << "I am lock " << QString::number(m_number);
    m_pauseMutex.lock();
    //qDebug() << "I am unlock " << QString::number(m_number);

    //qDebug() << "Пробую захватить " << QString::number(m_number) << " " << QString::number(staticMutexNamesspace::stiks[m_firstNumberStik.load()]->getNumberStick())
    //         << " " << QString::number(staticMutexNamesspace::stiks[m_secondNumberStik.load()]->getNumberStick());

    while(!pushTwoStick()){};
    //qDebug() << "I am start eating " << QString::number(m_number);
    m_eatingState = Eateing;
    tickEat();
}

void Philosopher::tickEat(){
    while(m_nowTime!=m_eatingTime){
        std::this_thread::sleep_for (std::chrono::seconds(1));
        m_nowTime++;
        if(m_nowTime == m_eatingTime){
            m_eatingState = FinishEateing;
            //qDebug() << "I am finish eating " << QString::number(m_number);
            staticMutexNamesspace::stiks[m_firstNumberStik.load()]->unlock();
            putStikcs(m_firstNumberStik.load(), false, m_number);
            staticMutexNamesspace::stiks[m_secondNumberStik.load()]->unlock();
            putStikcs(m_secondNumberStik.load(), false, m_number);
        }
        eating(m_nowTime, m_number, m_eatingState, std::pair<int,int>(m_firstNumberStik.load(),m_secondNumberStik.load()));
    }
}

bool Philosopher::pushTwoStick(){
    srand(unsigned(time(NULL)));
    int randNumber = rand()%400 + 750;
    if(staticMutexNamesspace::stiks[m_firstNumberStik.load()]->tryLock(randNumber)){
        putStikcs(m_firstNumberStik.load(), true, m_number);
        if(staticMutexNamesspace::stiks[m_secondNumberStik.load()]->tryLock(randNumber)){
            putStikcs(m_secondNumberStik.load(), true, m_number);
            return true;
        }
        else{
            putStikcs(m_firstNumberStik.load(), false, m_number);
            staticMutexNamesspace::stiks[m_firstNumberStik.load()]->unlock();
        }
    }
    return false;
}

void Philosopher::setNumber(int number)
{
    m_number = number;
}


