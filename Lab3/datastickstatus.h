#ifndef DATASTICKSTATUS_H
#define DATASTICKSTATUS_H
#include <enums.h>
#include <QTime>
class DataStickStatus
{
public:
    DataStickStatus();
    DataStickStatus(int const &numberStick, PushingStickEnum const &state);
    int getNumberStick(){return m_numberStick;}
    bool operator<(DataStickStatus &rhs) const {
        if(this->m_numberStick != rhs.getNumberStick()) return this->m_numberStick < rhs.getNumberStick();
        else{
            this->m_timeChangeState < rhs.m_timeChangeState;
        }
    }
private:
    int m_numberStick;
    PushingStickEnum m_state;
    QDateTime m_timeChangeState;
};

#endif // DATASTICKSTATUS_H
