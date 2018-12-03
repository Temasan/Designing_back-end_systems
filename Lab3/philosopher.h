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

//static std::mutex globalMutex;
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
    //void lock(){m_pauseMutex.lock();}//!< Блокировка локального мьютекса паузы
    void unlock(){m_pauseMutex.unlock();} //!< Разблокировка локального мьютекса паузы
    void setNumber(int number); //!< Задаем номер философа
signals:
    void eating(int nowtime, int number, EatingState eatingState, std::pair<int,int> sticks); //!< Сигнал логирование, что философ есть один такт времени
    void putStikcs(int stick, bool status, int numberPhyl); //!< Сигнал логирования о захвате или отпускания палки
    bool messageToDinnerSend(PushingStickEnum message, int numberPhylosopher); //!< Актор отправляет сообщение первому соседнему актору
private:
    bool pushTwoStick(); //!< Функция возвращает true, если философу удалось захватить две палки
    EatingState m_eatingState = NotEateing; //!< Текущий статус философа
    uint32_t m_eatingTime = 3; //!< Время, необходимое для питания философу
    uint32_t m_nowTime = 0; //!< Текущее время, которое показывает сколько кушает философ
    //std::atomic<bool> m_firstStateStik; //!< Состояние первой (левой) палочки. Если true, то палка свободна
    //std::atomic<bool> m_secondStateStik;//!< Состояние второй (правой) палочки. Если true, то палка свободна
    std::atomic<int> m_firstNumberStik; //!< Номер первой палочки
    std::atomic<int> m_secondNumberStik;//!< Номер второй палочки
    std::mutex m_pauseMutex; //!< Мьютекс паузы
    int m_number = -1; //!< Номер философа
private slots:
    void tickEat();//!< Тик поедания философом
};

#endif // PHILOSOPHER_H
