#ifndef ENUMS_H
#define ENUMS_H

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
/*!
 * \brief The PushingStickEnum enum
 */
enum PushingStickEnum{
    tryPushingLeft = 0,
    tryPushingRight = 1,
    unPushingLeft = 2,
    unPushingRight = 3,
    tryPushing,
    unPushing
};

#endif // ENUMS_H
