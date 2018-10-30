#ifndef STICK_H
#define STICK_H
#include <QMutex>
#include <memory>
#include <QDebug>

/*!
 * \brief The Stick class имеет свой номер. Наследован от мьютекса
 */
class Stick
{
public:
    explicit Stick(uint32_t numberStick);
    ~Stick();
    bool tryLock(){
        if(state) {
            state = false;
            return true;
        }
        else
            return false;
    }
    void unlock(){state = true;}
    uint32_t getNumberStick() const; //!< Возврат номера палки. Необходим в логировании
private:
    bool state = true;
    int m_numberStick = -1; //!< Номер палочки. Информация для логирования
};

#endif // STICK_H
