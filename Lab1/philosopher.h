#ifndef PHILOSOPHER_H
#define PHILOSOPHER_H
#include <stick.h>
#include <memory>
#include <QString>
#include <QTimer>
#include <QObject>
#include <enums.h>
#include <atomic>
#include <QThread>
#include <mutex>

/*!
 * \brief The staticMutexNamesspace struct Структура со статическим вектором палок. Причина использование - проблема с многопоточностью
 * при обращении к данным
 */
struct staticMutexNamesspace {
    staticMutexNamesspace(){}
    static std::vector<Stick*> stiks;
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
    void lock(){m_pauseMutex.lock();}//!< Блокировка локального мьютекса паузы
    void unlock(){m_pauseMutex.unlock();} //!< Разблокировка локального мьютекса паузы
    void setNumber(int number); //!< Задаем номер философа
signals:
    void eating(int nowtime, int number, EatingState eatingState, std::pair<int,int> sticks); //!< Сигнал логирование, что философ есть один такт времени
    void putStikcs(int stick, bool status, int numberPhyl); //!< Сигнал логирования о захвате или отпускания палки
private:
    bool pushTwoStick(); //!< Функция возвращает true, если философу удалось захватить две палки
    EatingState m_eatingState = NotEateing; //!< Текущий статус философа
    uint32_t m_eatingTime = 3; //!< Время, необходимое для питания философу
    uint32_t m_nowTime = 0; //!< Текущее время, которое показывает сколько кушает философ
    std::atomic<int> m_firstNumberStik; //!< Номер первой палочки
    std::atomic<int> m_secondNumberStik;//!< Номер второй палочки
    std::mutex m_pauseMutex; //!< Мьютекс паузы
    int m_number = -1; //!< Номер философа
private slots:
    void tickEat();//!< Тик поедания философом
};

#endif // PHILOSOPHER_H
