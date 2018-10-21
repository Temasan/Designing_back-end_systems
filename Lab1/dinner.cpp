#include "dinner.h"
#include <functional>
#include <QDebug>

//std::mutex staticMutexNamesspace::staticPauseMutex;
std::vector<Stick*> staticMutexNamesspace::stiks;


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
        std::this_thread::sleep_for (std::chrono::seconds(1));
        for(int i = 0; i< m_numberPhylosophers; i++){
            m_vectorPhilosophers[i]->unlock();
        }
        //staticMutexNamesspace::staticPauseMutex.unlock();
        //m_ptrMutex->unlock();
 //   m_timer->start();
    }
}

void Dinner::onEating(int nowtime, int number, EatingState eatingState){
    getPropertiesToWidget(QString::number(number), nowtime, eatingState);
}

void Dinner::init(){
    //staticMutexNamesspace::staticPauseMutex.lock();
    //m_timer = new QTimer(this);
    //QObject::connect(m_timer, SIGNAL(timeout()), this, SLOT(onTriggered()));
    //m_timer->setInterval(500);


   // m_ptrMutex = std::make_shared<std::mutex>();
   // m_ptrMutex->lock();
    //staticMutexNamesspace::stiks.resize(m_numberPhylosophers);
    for(uint32_t i = 0; i < m_numberPhylosophers; i++){
        staticMutexNamesspace::stiks.push_back(new Stick(i));
    }

    //srand(unsigned(time(NULL)));
    for(uint32_t i = 0; i < m_numberPhylosophers; i++){
        int two_stick = (i+1 != staticMutexNamesspace::stiks.size() ? (i+1):0);
        //int m = random()%10; //!\note 10 - максимальное время еды const
        m_vectorPhilosophers.push_back(new Philosopher(std::pair<int,int>(i,two_stick)/*m_vectorStics[i],m_vectorStics[two_stick],
                                       m_ptrMutex,*/));
        //m_vectorPhilosophers[i]->setName(m_names[i]);
        m_vectorPhilosophers[i]->setNumber(i);
        m_vectorPhilosophers[i]->lock();

        connect(m_vectorPhilosophers[i], SIGNAL(eating(int, int, EatingState)), this, SLOT(onEating(int,int,EatingState)),Qt::QueuedConnection);
        //m_vectorPhilosophers[i]->setEatingTime(m);
        /*m_vectorThreads.push_back(
                    new std::thread(std::bind(
                            &Philosopher::startEating,m_vectorPhilosophers[i])));*/
        m_vectorPhilosophers[i]->start();
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

