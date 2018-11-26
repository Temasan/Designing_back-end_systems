#include "dinner.h"
#include <functional>
#include <QDebug>


Dinner::Dinner(QObject*parent)
    :QObject(parent)
{

}

Dinner::~Dinner()
{

}

void Dinner::start(bool status){
    if(status){
        init();
        for(uint i = 0; i< m_numberPhylosophers; i++){
            m_vectorPhilosophers[i]->unlock();
        }
    }
}

void Dinner::onEating(int nowtime, int number, EatingState eatingState, std::pair<int, int> sticks){
    getPropertiesToWidget(QString::number(number), nowtime, eatingState,sticks);
}

void Dinner::onPutStick(int stick, bool status,int numberPhyl){
    putStick(stick,status,numberPhyl);
}

void Dinner::init(){
    // создание философов
    for(uint32_t i = 0; i < m_numberPhylosophers; i++){
        int two_stick = (i+1 != m_numberPhylosophers ? (i+1):0);
        m_vectorPhilosophers.push_back(new Philosopher(std::pair<int,int>(i,two_stick)));
        stateSticks.push_back(true);
    }
    // связывание философов друг с другом через сигнал-слот систему
    for(uint32_t i = 0; i < m_numberPhylosophers; i++){
        //int two_stick = (i+1 != m_numberPhylosophers ? (i+1):0);
        m_vectorPhilosophers[i]->setNumber(i);
        //m_vectorPhilosophers[i]->lock();
        //int oneNumberNeighboard = (i == 0 ? m_vectorPhilosophers.size()-1:i-1);

        connect(m_vectorPhilosophers[i], SIGNAL(eating(int, int, EatingState,std::pair<int,int>)), this, SLOT(onEating(int,int,EatingState,std::pair<int,int>)),Qt::QueuedConnection);
        connect(m_vectorPhilosophers[i], SIGNAL(putStikcs(int, bool,int)), this, SLOT(onPutStick(int, bool,int)),Qt::QueuedConnection);

        // соединяем методы соседних философов для передачи сообщений
        connect(m_vectorPhilosophers[i], SIGNAL(messageToDinnerSend(PushingStickEnum, int)),
                this, SLOT(onMessageFromphylosopher(PushingStickEnum,int)),Qt::BlockingQueuedConnection);

        /*connect(m_vectorPhilosophers[i], SIGNAL(messageToOneNeighbourSend(Philosopher::PushingStickEnum)),
                m_vectorPhilosophers[oneNumberNeighboard], SLOT(onMessageFromNeighbourSend(Philosopher::PushingStickEnum)),Qt::BlockingQueuedConnection);
        connect(m_vectorPhilosophers[i], SIGNAL(messageToTwoNeighbourSend(Philosopher::PushingStickEnum)),
                m_vectorPhilosophers[two_stick], SLOT(onMessageFromNeighbourSend(Philosopher::PushingStickEnum)),Qt::BlockingQueuedConnection);
*/
        m_vectorPhilosophers[i]->start();
    }
}

void Dinner::setNumberPhylosophers(int numberPhylosophers)
{
    m_numberPhylosophers = numberPhylosophers;
}

bool Dinner::onMessageFromphylosopher(PushingStickEnum message, int numberPhylosopher){
    int numberRightStick = numberPhylosopher + 1 == m_numberPhylosophers? 0:numberPhylosopher+1;
    switch(message){
    case tryPushingLeft: // сосед просит взять левую палку, для текущего философа это правая
       if(stateSticks[numberPhylosopher]){
            stateSticks[numberPhylosopher] = false;
            return true;
        }
        break;
     case tryPushingRight: // сосед просит взять правую палку, для текущего философа это левая
        if(stateSticks[numberRightStick]){
            stateSticks[numberRightStick] = false;
            return true;
        }
        break;
     case unPushingLeft: // сосед говорит, что больше не использует палку
        stateSticks[numberPhylosopher] = true;
        return true;
     case unPushingRight: // сосед говорит, что больше не использует палку
        stateSticks[numberRightStick] = true;
        return true;
    }
    return false;
}

