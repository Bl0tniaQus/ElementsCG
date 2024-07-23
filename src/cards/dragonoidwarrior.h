#ifndef DRAGONOIDWARRIOR_H
#define DRAGONOIDWARRIOR_H
#include "cardbase.h"
class DragonoidWarrior : public CardBase
{
public:
    DragonoidWarrior():CardBase(
        3, //card id
        3, //cost
        1, //card type (0 - spell, 1 - minion, 2 - spminion)
        3, //level
        2, //attack
        2, //defence
        "Air", //element
        "Dragonoid Warrior", //name
        "dragonoidwarrior",
        ""
    ) {};
};

#endif
