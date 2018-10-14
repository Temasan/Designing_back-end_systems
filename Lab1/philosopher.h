#ifndef PHILOSOPHER_H
#define PHILOSOPHER_H
#include <stick.h>
#include <memory>
#include <QString>
#include <QTimer>
#include <QObject>
#include <enums.h>
#include <atomic>

typedef std::shared_ptr<Stick> ptrStick;

/*!
 * \brief The EatingState enum Статус философа:
 *  - не начинал кушать;
 *  - кушает;
 *  - закончил кушать.
 */

class Philosopher : public QObject
{
    Q_OBJECT
public:
    explicit Philosopher(ptrStick stickOne, ptrStick stickTwo,std::shared_ptr<std::mutex> ptrMutex, QObject * parent=nullptr);
    void startEating(); //!< Метод, вызываемый ассинхронным потоком
    EatingState getEatingState(){return m_eatingState;} const
    void setEatingTime(uint32_t eatingTime){m_eatingTime = eatingTime;}
    uint32_t getNowTime() const {return m_nowTime;}
    QString getName() const {return m_name;}
    void setName(const QString &name){m_name = name;}
    int getNumber() const;
    void setNumber(int number);
    bool getStarted() const;
signals:
    void eating(int nowtime, int number, EatingState eatingState); //!< Философ есть определенный тик времени
private:
    bool pushTwoStick(); //!< Функция возвращает true, если философу удалось захватить две палки
    std::pair<ptrStick, ptrStick> m_pairSticks; //!< Левая и правая палочка, необходимые философу для питания
    EatingState m_eatingState = NotEateing; //!< Текущий статус философа
    std::shared_ptr<std::mutex> m_pauseMutex; //!< Мьютекс паузы (кушать ещё не начинал либо ждет тика таймера)
    uint32_t m_eatingTime = 5; //!< Время, необходимое для питания философу
    uint32_t m_nowTime = 0; //!< Текущее время, которое показывает сколько кушает философ
    QString m_name = ""; //!< Имя философа
    int m_number = -1;
    bool m_started = false;
    //QTimer *m_timer;
private slots:
    void tickEat();
};

#endif // PHILOSOPHER_H
