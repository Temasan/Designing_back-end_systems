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
  //  qDebug() << QString::number(stick) << " " << QString::number(status);
    putStick(stick,status,numberPhyl);
}

void Dinner::init(){
    for(uint32_t i = 0; i < m_numberPhylosophers; i++){
        int two_stick = (i+1 != m_numberPhylosophers ? (i+1):0);
        m_vectorPhilosophers.push_back(new Philosopher(std::pair<int,int>(i,two_stick)));
        m_vectorPhilosophers[i]->setNumber(i);
        m_vectorPhilosophers[i]->lock();
        int oneNumberNeighboard = (i == 0 ? m_vectorPhilosophers.size()-1:i-1);
        int twoNumberNeighboard = two_stick;

        connect(m_vectorPhilosophers[i], SIGNAL(eating(int, int, EatingState,std::pair<int,int>)), this, SLOT(onEating(int,int,EatingState,std::pair<int,int>)),Qt::QueuedConnection);
        connect(m_vectorPhilosophers[i], SIGNAL(putStikcs(int, bool,int)), this, SLOT(onPutStick(int, bool,int)),Qt::QueuedConnection);

        // соединяем методы соседних философов для передачи сообщений
        connect(m_vectorPhilosophers[i], SIGNAL(messageToOneNeighbourSend(Philosopher::PushingStickEnum)),
                m_vectorPhilosophers[oneNumberNeighboard], SLOT(onMessageFromNeighbourSend(Philosopher::PushingStickEnum)),Qt::QueuedConnection);
        connect(m_vectorPhilosophers[i], SIGNAL(messageToTwoNeighbourSend(Philosopher::PushingStickEnum)),
                m_vectorPhilosophers[twoNumberNeighboard], SLOT(onMessageFromNeighbourSend(Philosopher::PushingStickEnum)),Qt::QueuedConnection);

        m_vectorPhilosophers[i]->start();
    }
}

void Dinner::setNumberPhylosophers(int numberPhylosophers)
{
    m_numberPhylosophers = numberPhylosophers;
}

