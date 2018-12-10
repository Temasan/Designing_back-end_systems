#include "philosopher.h"
#include <QDebug>
#include <chrono>
#include <thread>
#include <QDateTime>
Philosopher::Philosopher(std::pair<int, int> pairSticsNumber, QThread *parent):
    QThread(parent)
{
    m_firstNumberStik.store(pairSticsNumber.first);
    m_secondNumberStik.store(pairSticsNumber.second);
    m_firstStateStik.store(true);
    m_secondStateStik.store(true);
    m_pauseMutex.lock();
    m_firstStikTimePushing.store(0);
    m_secondStikTimePushing.store(0);
    m_itEating.store(false);
}

void Philosopher::run(){
    m_pauseMutex.lock();
    while(!pushTwoStick()){
        // когда палки захватить не получилось, то данные все сбрасываются, а взятые палки отпускаются
        srand(unsigned(time(NULL)));
        int randNumber = rand()%400 + 750;
        //m_firstStateStik.store(false);
        //m_firstStikTimePushing.store(0);
        putStikcs(m_firstNumberStik.load(), false, m_number);

        //m_secondStateStik.store(false);
        //m_secondStikTimePushing.store(0);
        putStikcs(m_secondNumberStik.load(), false, m_number);

        std::this_thread::sleep_for (std::chrono::milliseconds(randNumber));
    };
    m_eatingState = Eateing;
    tickEat();
}

void Philosopher::tickEat(){
    while(m_nowTime!=m_eatingTime){
        std::this_thread::sleep_for (std::chrono::seconds(1));
        m_nowTime++;
        if(m_nowTime == m_eatingTime){
            //qDebug() << QString::number(m_number) +" unpush";
            m_firstStikTimePushing.store(0);
            m_firstStateStik.store(true);
            //messageToDinnerSend();
            putStikcs(m_firstNumberStik.load(), false, m_number);

            //qDebug() << QString::number(m_number) +" unpush"+QString::number(m_secondNumberStik.load());
            m_secondStikTimePushing.store(0);
            m_secondStateStik.store(true);
            //messageToDinnerSend();
            putStikcs(m_secondNumberStik.load(), false, m_number);
            m_eatingState = FinishEateing;
        }
        qDebug() << QString::number(m_number) +" eating";
        eating(m_nowTime, m_number, m_eatingState, std::pair<int,int>(m_firstNumberStik.load(),m_secondNumberStik.load()));
    }
}

bool Philosopher::pushTwoStick(){
    if(m_itEating.load())
        return m_itEating.load();
    phylosophersGlobal::vectorOfMutex[m_number]->lock();
    if(m_firstStateStik.load()){
        m_firstStateStik.store(false);
        m_firstStikTimePushing.store(QDateTime::currentDateTime().toMSecsSinceEpoch());
        putStikcs(m_firstNumberStik.load(), true, m_number);
        if(m_secondStateStik.load()){
            m_secondStateStik.store(false);
            m_secondStikTimePushing.store(QDateTime::currentDateTime().toMSecsSinceEpoch());
            putStikcs(m_secondNumberStik.load(), true, m_number);
            qDebug() << QString::number(m_number) << " locking";
            phylosophersGlobal::vectorOfMutex[m_number]->lock();
            qDebug() << QString::number(m_number) << " unlocking";

            return m_itEating.load();
        }
    }
    phylosophersGlobal::vectorOfMutex[m_number]->unlock();
    return false;
}

void Philosopher::setNumber(uint32_t number)
{
    m_number = number;
}

void Philosopher::calculateKingStates(){

    //qDebug() << " start kingPhase";
    // рассматриваем каждого философа
    for(uint i = 0; i < phylosophersGlobal::m_vectorPhilosophers.size(); i++){
        unsigned long int leftPhylosoherTime =
                phylosophersGlobal::m_vectorPhilosophers[i != 0 ? i-1 : phylosophersGlobal::m_vectorPhilosophers.size()-1]->getSecondStickPushingTime();
        unsigned long int rightPhylosoherTime =
                phylosophersGlobal::m_vectorPhilosophers[i+1 != phylosophersGlobal::m_vectorPhilosophers.size() ? (i+1):0]->getFirstStickPushingTime();
        unsigned long int leftStickTime = phylosophersGlobal::m_vectorPhilosophers[i]->getFirstStickPushingTime();
        unsigned long int rightStickTime = phylosophersGlobal::m_vectorPhilosophers[i]->getSecondStickPushingTime();
        bool leftPhylosopherStatus = phylosophersGlobal::m_vectorPhilosophers[i != 0 ? i-1 : phylosophersGlobal::m_vectorPhilosophers.size()-1]->getIsEating();
        bool rightPhylosopherStatus = phylosophersGlobal::m_vectorPhilosophers[i+1 != phylosophersGlobal::m_vectorPhilosophers.size() ? (i+1):0]->getIsEating();

        /*qDebug() << QString::number(leftPhylosoherTime) << " leftPhylosoherTime";
        qDebug() << QString::number(rightPhylosoherTime) << " rightPhylosoherTime";
        qDebug() << QString::number(leftStickTime) << " leftStickTime";
        qDebug() << QString::number(rightStickTime) << " rightStickTime";
        qDebug() << QString::number(rightStickTime) << " rightStickTime";
*/
        // условие, при котором время захвата левой палки не равно нулю и это время меньше времени захвата этой же палки его правого соседа либо же время
        // захвата равно нулю и такой же набор условий для правого соседа
        if(( leftStickTime!= 0 && (leftStickTime <= leftPhylosoherTime  || leftPhylosoherTime == 0))
                && ( rightStickTime!= 0 && (rightStickTime <= rightPhylosoherTime  || rightPhylosoherTime == 0))
                && !leftPhylosopherStatus && !rightPhylosopherStatus){
            qDebug() << QString::number(i) << " I am start";

            phylosophersGlobal::m_vectorPhilosophers[i]->setEating(true);
        }
        // если философ закончил кушать, то его палки следует отпустить у других философов
        else if(phylosophersGlobal::m_vectorPhilosophers[i]->getEatingStatus() == EatingState::FinishEateing){
            phylosophersGlobal::m_vectorPhilosophers[i != 0 ? i-1 : phylosophersGlobal::m_vectorPhilosophers.size()-1]->setFirstStickStatus(true);
            phylosophersGlobal::m_vectorPhilosophers[i+1 != phylosophersGlobal::m_vectorPhilosophers.size() ? (i+1):0]->setSecondStickStatus(true);
        }
    }
    for(uint i = 0; i < phylosophersGlobal::m_vectorPhilosophers.size(); i++){
        phylosophersGlobal::vectorOfMutex[i]->unlock();
    }
}
