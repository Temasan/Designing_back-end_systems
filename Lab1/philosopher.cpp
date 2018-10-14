#include "philosopher.h"
#include <QDebug>
#include <chrono>
#include <thread>

Philosopher::Philosopher(ptrStick stickOne, ptrStick stickTwo, std::shared_ptr<std::mutex> ptrMutex, QObject *parent):
    QObject(parent),
    m_pairSticks(stickOne,stickTwo),
    m_pauseMutex(ptrMutex)
{
   // m_pairSticks.first = stickOne;
   // m_pairSticks.second = stickTwo;
    //m_pauseMutex = std::move(ptrMutex);
//    m_timer = new QTimer(this);
//    m_timer->setInterval(1000);
    //QObject::connect(m_timer, SIGNAL(timeout()), this, SLOT(tickEat()));
}

void Philosopher::startEating(){
    qDebug() << "I am lock " << QString::number(m_number);
    m_started = true;
    m_pauseMutex->lock();
    qDebug() << "I am unlock " << QString::number(m_number);
    while(!pushTwoStick()){};
    qDebug() << "I am start eating " << QString::number(m_number);
    m_eatingState = Eateing;
//    m_timer->start();
    tickEat();
}

void Philosopher::tickEat(){
    while(m_nowTime!=m_eatingTime){
        std::this_thread::sleep_for (std::chrono::seconds(1));
        m_nowTime++;
        if(m_nowTime==m_eatingTime){
    //        m_timer->stop();
            m_eatingState = FinishEateing;
            m_pairSticks.first->unLock();
            m_pairSticks.second->unLock();        }
        eating(m_nowTime, m_number, m_eatingState);
    }
}

bool Philosopher::pushTwoStick(){
    qDebug() << "Пробую захватить " << QString::number(m_number);
    if(m_pairSticks.first->tryLock() && m_pairSticks.second->tryLock()){
        return true;
    }
    else if(!m_pairSticks.second->tryLock()){
        m_pairSticks.second->lock(); // принудительный захват. Если палку взять нельзя, то залочить мьютекс
        return false; // и вернуться в бесконечный цикл после отпускания
    }
    else if(!m_pairSticks.first->tryLock()){
        m_pairSticks.first->lock();
        return false;
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


