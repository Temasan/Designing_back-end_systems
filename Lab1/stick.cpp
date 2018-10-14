#include "stick.h"

Stick::Stick(uint32_t numberStick){
    m_numberStick = numberStick;
    m_mutex = new std::mutex();
}
Stick::~Stick(){
    delete m_mutex;
}

uint32_t Stick::getNumberStick() const{
    return m_numberStick;
}

