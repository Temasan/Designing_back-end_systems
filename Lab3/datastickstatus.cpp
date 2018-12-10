#include "datastickstatus.h"

DataStickStatus::DataStickStatus()
{
    m_timeChangeState = QDateTime::currentDateTime();
}

DataStickStatus::DataStickStatus(const int &numberStick, const PushingStickEnum &state){
    m_timeChangeState = QDateTime::currentDateTime();
    m_state = state;
    m_numberStick = numberStick;
}
