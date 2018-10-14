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
#endif // ENUMS_H
