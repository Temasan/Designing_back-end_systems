#include "stick.h"

Stick::Stick(uint32_t numberStick){
    m_numberStick = numberStick;
}
Stick::~Stick(){}

uint32_t Stick::getNumberStick() const{
    return m_numberStick;
}

