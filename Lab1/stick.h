#ifndef STICK_H
#define STICK_H
#include <QMutex>
#include <memory>
#include <QDebug>

/*!
 * \brief The Stick class имеет свой номер. Наследован от мьютекса
 */
class Stick: public QMutex
{
public:
    explicit Stick(uint32_t numberStick);
    ~Stick();
    uint32_t getNumberStick() const; //!< Возврат номера палки. Необходим в логировании
private:
    int m_numberStick = -1; //!< Номер палочки. Информация для логирования
};

#endif // STICK_H
