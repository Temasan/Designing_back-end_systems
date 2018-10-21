#ifndef ENUMS_H
#define ENUMS_H
#include <thread>
#include <mutex>
#include <atomic>


/*!
 * \brief The EatingState enum Статус философа:
 *  - не начинал кушать;
 *  - кушает;
 *  - закончил кушать.
 */

enum EatingState{
    NotEateing = 0,
    Eateing,
    FinishEateing
};

typedef std::shared_ptr<std::atomic<std::mutex>> ptrAtomicMutex;
typedef std::shared_ptr<std::mutex> ptrMutex;


#endif // ENUMS_H
