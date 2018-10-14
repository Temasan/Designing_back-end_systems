#ifndef STICK_H
#define STICK_H
#include <mutex>
#include <memory>
#include <QDebug>

class Stick
{
public:
    explicit Stick(uint32_t numberStick);
    ~Stick();
    uint32_t getNumberStick() const; //!< Возврат номера палки. Необходим в логировании
    bool tryLock(){
        qDebug() << QString::number(m_numberStick);
      //  return m_mutex->try_lock();
    }
    void lock(){m_mutex->lock();}
    void unLock(){m_mutex->unlock();}
private:
    std::mutex* m_mutex; //!< Мьютекс для захвата и блокировки философом
    int m_numberStick = -1; //!< Номер палочки. Информация для логирования
};

#endif // STICK_H
