#ifndef PHILOSOPHER_H
#define PHILOSOPHER_H
#include <memory>
#include <QString>
#include <QTimer>
#include <QObject>
#include <enums.h>
#include <atomic>
#include <QThread>
#include <mutex>
#include <enums.h>

/*!
 * \brief The stickMaster struct - общая дублирующая структура, позволяющая текущему философу проверить, что он является хозяином палки
 */
/*struct stickMaster
{
    static std::vector<std::pair<int,uint>> vectorOfMastersStick;
};*/

class Philosopher;
typedef std::vector<Philosopher*> vectorPhilosophers;

struct phylosophersGlobal
{
    static std::vector<std::mutex*> vectorOfMutex;
    static vectorPhilosophers m_vectorPhilosophers;
};

/*!
 * \brief The Philosopher class наследован от потока. Работает параллельно. Обращяется к статическому вектору просранства имен staticMutexNamesspace
 */
class Philosopher : public QThread
{
    Q_OBJECT
public:
    explicit Philosopher(std::pair<int,int> pairSticsNumber, QThread *parent=nullptr);
    void run() override;
    void setEatingTime(uint32_t eatingTime){m_eatingTime = eatingTime;}
    void unlock(){m_pauseMutex.unlock();} //!< Разблокировка локального мьютекса паузы
    void setNumber(uint32_t number); //!< Задаем номер философа
    //int getNumber(){return m_number;}
    void setFirstStickStatus(bool firstStateStik){m_firstStateStik.store(firstStateStik);}
    void setSecondStickStatus(bool secondStateStik){m_secondStateStik.store(secondStateStik);}
    unsigned long int getFirstStickPushingTime(){return m_firstStikTimePushing.load();}
    unsigned long int getSecondStickPushingTime(){return m_secondStikTimePushing.load();}
    void setFirstStickPushingTime(unsigned long int time){m_firstStikTimePushing.store(time);}
    void setSecondStickPushingTime(unsigned long int time){m_secondStikTimePushing.store(time);}
    void setEating(bool status){m_itEating.store(status);}
    EatingState getEatingStatus() {return m_eatingState;}
    bool getIsEating(){return m_itEating;}
signals:
    void eating(int nowtime, int number, EatingState eatingState, std::pair<int,int> sticks); //!< Сигнал логирование, что философ есть один такт времени
    void putStikcs(int stick, bool status, int numberPhyl); //!< Сигнал логирования о захвате или отпускания палки
    bool messageToDinnerSend(); //!< Актор отправляет сообщение первому соседнему актору
//    std::vector<DataStickStatus> updateData(std::vector<DataStickStatus> const&); //!< Философу назначается обязаность проверить данные всех философов
public slots:
    void calculateKingStates();
private:
    bool pushTwoStick(); //!< Функция возвращает true, если философу удалось захватить две палки
    EatingState m_eatingState = NotEateing; //!< Текущий статус философа
    uint32_t m_eatingTime = 3; //!< Время, необходимое для питания философу
    uint32_t m_nowTime = 0; //!< Текущее время, которое показывает сколько кушает философ
    std::atomic<bool> m_firstStateStik; //!< Состояние первой (левой) палочки. Если true, то палка свободна
    std::atomic<bool> m_secondStateStik;//!< Состояние второй (правой) палочки. Если true, то палка свободна
    std::atomic<int> m_firstNumberStik; //!< Номер первой палочки
    std::atomic<int> m_secondNumberStik;//!< Номер второй палочки
    std::atomic<unsigned long int> m_firstStikTimePushing; //!< Время захвата одной палки
    std::atomic<unsigned long int> m_secondStikTimePushing;//!< Время захвата одной палки
    std::atomic<bool> m_itEating;

    std::mutex m_pauseMutex; //!< Мьютекс паузы
    uint32_t m_number = -1; //!< Номер философа
private slots:
    void tickEat();//!< Тик поедания философом
};

#endif // PHILOSOPHER_H
