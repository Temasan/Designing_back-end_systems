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
            m_eatingState = FinishEateing;
            //qDebug() << "I am finish eating " << QString::number(m_number);
            messageToOneNeighbourSend(unPushingLeft);
            m_firstStateStik.store(true);
            putStikcs(m_firstNumberStik.load(), false, m_number);
            messageToOneNeighbourSend(unPushingRight);
            m_secondNumberStik.store(true);
            putStikcs(m_secondNumberStik.load(), false, m_number);
        }
        eating(m_nowTime, m_number, m_eatingState, std::pair<int,int>(m_firstNumberStik.load(),m_secondNumberStik.load()));
    }
}

bool Philosopher::onMessageFromNeighbourSend(PushingStickEnum message){
    switch(message){
    case tryPushingLeft: // сосед просит взять левую палку, для текущего философа это правая
        if(m_secondNumberStik.load()){
            m_secondNumberStik.store(false);
            return true;
        }
        return false;
     case tryPushingRight: // сосед просит взять правую палку, для текущего философа это левая
        if(m_firstNumberStik.load()){
            m_firstNumberStik.store(false);
            return true;
        }
        return false;
     case unPushingLeft: // сосед говорит, что больше не использует палку
         m_secondNumberStik.store(true);
         return true;
     case unPushingRight: // сосед говорит, что больше не использует палку
        m_firstNumberStik.store(true);
        return true;
    }
    return false;
}


bool Philosopher::pushTwoStick(){
    srand(unsigned(time(NULL)));
    int randNumber = rand()%400 + 750;
    if(messageToOneNeighbourSend(tryPushingLeft)){ // попытка захватить левую палку, которая для соседа является правой
        m_firstStateStik.store(false);
        putStikcs(m_firstNumberStik.load(), true, m_number);
        if(messageToOneNeighbourSend(tryPushingRight)){ // попытка захватить правую палку, которая для соседа является левой
            m_secondNumberStik.store(false);
            putStikcs(m_secondNumberStik.load(), true, m_number);
            return true;
        }
        else{
            m_firstStateStik.store(true);
            messageToOneNeighbourSend(unPushingLeft);
            putStikcs(m_firstNumberStik.load(), false, m_number);
        }
    }
    std::this_thread::sleep_for (std::chrono::seconds(randNumber));
    return false;
}

void Philosopher::setNumber(int number)
{
    m_number = number;
}


