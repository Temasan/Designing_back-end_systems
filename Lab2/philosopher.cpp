#include "philosopher.h"
#include <QDebug>
#include <chrono>
#include <thread>

Philosopher::Philosopher(std::pair<int, int> pairSticsNumber, QThread *parent):
    QThread(parent)
{
    m_firstNumberStik.store(pairSticsNumber.first);
    m_secondNumberStik.store(pairSticsNumber.second);
    m_secondStateStik.store(true);
    m_firstStateStik.store(true);
}

void Philosopher::run(){
    m_pauseMutex.lock();
    while(!pushTwoStick()){};
    m_eatingState = Eateing;
    tickEat();
}

void Philosopher::tickEat(){
    while(m_nowTime!=m_eatingTime){
        std::this_thread::sleep_for (std::chrono::seconds(1));
        m_nowTime++;
        if(m_nowTime == m_eatingTime){
            globalMutex.lock();
            m_eatingState = FinishEateing;
            qDebug() << QString::number(m_number) +" unpush"+QString::number(m_firstNumberStik.load());
            messageToOneNeighbourSend(unPushingLeft);
            m_firstStateStik.store(true);
            putStikcs(m_firstNumberStik.load(), false, m_number);
            qDebug() << QString::number(m_number) +" unpush"+QString::number(m_secondNumberStik.load());
            messageToOneNeighbourSend(unPushingRight);
            m_secondStateStik.store(true);
            putStikcs(m_secondNumberStik.load(), false, m_number);
            globalMutex.unlock();
        }
        eating(m_nowTime, m_number, m_eatingState, std::pair<int,int>(m_firstNumberStik.load(),m_secondNumberStik.load()));
    }
}

bool Philosopher::onMessageFromNeighbourSend(Philosopher::PushingStickEnum message){
    switch(message){
    case tryPushingLeft: // сосед просит взять левую палку, для текущего философа это правая
       if(m_secondStateStik.load()){
            m_secondStateStik.store(false);
            return true;
        }
        break;
     case tryPushingRight: // сосед просит взять правую палку, для текущего философа это левая
         if(m_firstStateStik.load()){
            m_firstStateStik.store(false);
            return true;
        }
        break;
     case unPushingLeft: // сосед говорит, что больше не использует палку
         m_secondStateStik.store(true);
         return true;
     case unPushingRight: // сосед говорит, что больше не использует палку
        m_firstStateStik.store(true);
        return true;
    }
    return false;
}

bool Philosopher::pushTwoStick(){
    srand(unsigned(time(NULL)));
    int randNumber = rand()%400 + 750;
    globalMutex.lock();
    if(messageToOneNeighbourSend(tryPushingLeft) && m_firstStateStik.load()){ // попытка захватить левую палку, которая для соседа является правой
        m_firstStateStik.store(false);
        putStikcs(m_firstNumberStik.load(), true, m_number);
        if(messageToTwoNeighbourSend(tryPushingRight) && m_secondStateStik.load()){ // попытка захватить правую палку, которая для соседа является левой
             m_secondStateStik.store(false);
            putStikcs(m_secondNumberStik.load(), true, m_number);
            globalMutex.unlock();
            return true;
        }
        else{
            m_firstStateStik.store(true);
            messageToOneNeighbourSend(unPushingLeft);
            putStikcs(m_firstNumberStik.load(), false, m_number);
        }
    }
    globalMutex.unlock();
    std::this_thread::sleep_for (std::chrono::milliseconds(randNumber));
    return false;
}

void Philosopher::setNumber(int number)
{
    m_number = number;
}


