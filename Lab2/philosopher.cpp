#include "philosopher.h"
#include <QDebug>
#include <chrono>
#include <thread>

Philosopher::Philosopher(std::pair<int, int> pairSticsNumber, QThread *parent):
    QThread(parent)
{
    m_firstNumberStik.store(pairSticsNumber.first);
    m_secondNumberStik.store(pairSticsNumber.second);
    m_pauseMutex.lock();

    //    m_secondStateStik.store(true);
//    m_firstStateStik.store(true);
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
            //globalMutex.lock();
            m_eatingState = FinishEateing;
            qDebug() << QString::number(m_number) +" unpush";
            messageToDinnerSend(unPushingLeft, m_number);
            //m_firstStateStik.store(true);
            putStikcs(m_firstNumberStik.load(), false, m_number);
            //qDebug() << QString::number(m_number) +" unpush"+QString::number(m_secondNumberStik.load());
            messageToDinnerSend(unPushingRight,m_number);
            //m_secondStateStik.store(true);
            putStikcs(m_secondNumberStik.load(), false, m_number);
           // globalMutex.unlock();
        }
        eating(m_nowTime, m_number, m_eatingState, std::pair<int,int>(m_firstNumberStik.load(),m_secondNumberStik.load()));
    }
}

bool Philosopher::pushTwoStick(){
    srand(unsigned(time(NULL)));
    int randNumber = rand()%400 + 750;
    //qDebug() << QString::number(m_number) << " tryining push";
    if(messageToDinnerSend(tryPushingLeft,m_number)){ // попытка захватить левую палку, которая для соседа является правой
       // m_firstStateStik.store(false);
        putStikcs(m_firstNumberStik.load(), true, m_number);
        if(messageToDinnerSend(tryPushingRight,m_number)){ // попытка захватить правую палку, которая для соседа является левой
         //    m_secondStateStik.store(false);
            putStikcs(m_secondNumberStik.load(), true, m_number);
           // globalMutex.unlock();
            return true;
        }
        else{
           // m_firstStateStik.store(true);
            messageToDinnerSend(unPushingLeft, m_number);
            putStikcs(m_firstNumberStik.load(), false, m_number);
        }
    }
    //globalMutex.unlock();
    std::this_thread::sleep_for (std::chrono::milliseconds(randNumber));
    return false;
}

void Philosopher::setNumber(int number)
{
    m_number = number;
}


