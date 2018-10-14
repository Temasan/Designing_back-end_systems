#include "dinner.h"
#include <functional>
#include <QDebug>

Dinner::Dinner(QObject*parent)
    :QObject(parent)
{
   // m_numberPhylosophers = numberPhylosophers;
    //m_names.insert(m_names.begin(),names.begin(),names.end());
   // init();
}

Dinner::~Dinner()
{

}

void Dinner::start(bool status){
    if(status){
        init();
        for(int i = 0; i< m_numberPhylosophers; i++){
            while(!m_vectorPhilosophers[i]->getStarted()){};
        }
        /*for(int i = 0; i< m_numberPhylosophers; i++){
            m_vectorPhilosophers[i]->getPauseMutex()->unlock();
        }*/

        m_ptrMutex->unlock();
 //   m_timer->start();
    }
}

void Dinner::onEating(int nowtime, int number, EatingState eatingState){
    getPropertiesToWidget(QString::number(number), nowtime, eatingState);
}

void Dinner::init(){
    //m_timer = new QTimer(this);
    //QObject::connect(m_timer, SIGNAL(timeout()), this, SLOT(onTriggered()));
    //m_timer->setInterval(500);


    m_ptrMutex = std::make_shared<std::mutex>();
    m_ptrMutex->lock();
    for(uint32_t i = 0; i < m_numberPhylosophers; i++){
        m_vectorStics.push_back(std::make_shared<Stick>(i));
    }
    //srand(unsigned(time(NULL)));
    for(uint32_t i = 0; i < m_numberPhylosophers; i++){
        int two_stick = (i+1 != m_vectorStics.size() ? (i+1):0);
        //int m = random()%10; //!\note 10 - максимальное время еды const
        m_vectorPhilosophers.push_back(new Philosopher(m_vectorStics[i],m_vectorStics[two_stick],
                                       std::move(m_ptrMutex), this));
        //m_vectorPhilosophers[i]->setName(m_names[i]);
        m_vectorPhilosophers[i]->setNumber(i);
        connect(m_vectorPhilosophers[i], SIGNAL(eating(int, int, EatingState)), this, SLOT(onEating(int,int,EatingState)));
        //m_vectorPhilosophers[i]->setEatingTime(m);
        m_vectorThreads.push_back(new std::thread(std::bind(&Philosopher::startEating, m_vectorPhilosophers[i])));
        //m_vectorThreads[i]->join();
    }
}

uint32_t Dinner::getNumberPhylosophers() const
{
    return m_numberPhylosophers;
}

void Dinner::setNumberPhylosophers(int numberPhylosophers)
{
    m_numberPhylosophers = numberPhylosophers;
}

