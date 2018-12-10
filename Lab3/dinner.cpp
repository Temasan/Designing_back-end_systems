#include "dinner.h"
#include <functional>
#include <QDebug>
#include <mutex>

std::vector<std::mutex*> phylosophersGlobal::vectorOfMutex;

vectorPhilosophers phylosophersGlobal::m_vectorPhilosophers;
//std::vector<std::pair<int,uint>> stickMaster::vectorOfMastersStick;

Dinner::Dinner(QObject*parent)
    :QObject(parent)
{
    m_numberKing.store(0);
   // m_tickTimer = new QTimer(this);
}

Dinner::~Dinner()
{
    //delete m_tickTimer;
}

void Dinner::start(bool status){
    if(status){
        init();
        m_tickTimer.start();
        for(uint i = 0; i< m_numberPhylosophers; i++){
            phylosophersGlobal::m_vectorPhilosophers[i]->unlock();
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
        phylosophersGlobal::m_vectorPhilosophers.push_back(new Philosopher(std::pair<int,int>(i,two_stick)));
        phylosophersGlobal::vectorOfMutex.push_back(new std::mutex());
    }
    // связывание философов друг с другом через сигнал-слот систему
    for(uint32_t i = 0; i < m_numberPhylosophers; i++){
        phylosophersGlobal::m_vectorPhilosophers[i]->setNumber(i);

        connect(phylosophersGlobal::m_vectorPhilosophers[i], SIGNAL(eating(int, int, EatingState,std::pair<int,int>)), this, SLOT(onEating(int,int,EatingState,std::pair<int,int>)),Qt::QueuedConnection);
        connect(phylosophersGlobal::m_vectorPhilosophers[i], SIGNAL(putStikcs(int, bool,int)), this, SLOT(onPutStick(int, bool,int)),Qt::QueuedConnection);

        // соединяем методы соседних философов для передачи сообщений столовой
        /*connect(phylosophersGlobal::m_vectorPhilosophers[i], SIGNAL(messageToDinnerSend()),
                this, SLOT(onMessageFromphylosopher()),Qt::BlockingQueuedConnection);
        phylosophersGlobal::m_vectorPhilosophers[i]->start();*/
        phylosophersGlobal::m_vectorPhilosophers[i]->start();
    }
    m_tickTimer.setInterval(1000);

    connect(&m_tickTimer, &QTimer::timeout, [&] () {
        bool stop_timer = true;
        phylosophersGlobal::m_vectorPhilosophers[m_numberKing.load()]->calculateKingStates();
        m_numberKing++;
        if(m_numberKing.load() == (unsigned long int)m_numberPhylosophers)
            m_numberKing.store(0);
        for(auto it = phylosophersGlobal::m_vectorPhilosophers.begin(); it != phylosophersGlobal::m_vectorPhilosophers.end(); it++){
            if((*it)->getEatingStatus() != EatingState::FinishEateing)
                stop_timer = false;
        }
        if(stop_timer){
            m_tickTimer.stop();
        }
    });
}

void Dinner::setNumberPhylosophers(int numberPhylosophers)
{
    m_numberPhylosophers = numberPhylosophers;
}


