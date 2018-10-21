#ifndef STICK_H
#define STICK_H
#include <QMutex>
#include <memory>
#include <QDebug>

class Stick: public QMutex
{
public:
    explicit Stick(uint32_t numberStick);
    ~Stick();
    uint32_t getNumberStick() const; //!< Возврат номера палки. Необходим в логировании
   /* bool tryLock(){
        //std::unique_lock<std::mutex>guard1((*m_mutex),std::defer_lock);
        return std::try_lock(m_mutex,) == 0? true:false;
    }
    void lock() const {m_mutex->lock();}
    void unLock() const {m_mutex->unlock();}*/
private:
    //std::mutex* m_mutex; //!< Мьютекс для захвата и блокировки философом
    int m_numberStick = -1; //!< Номер палочки. Информация для логирования
};

#endif // STICK_H
