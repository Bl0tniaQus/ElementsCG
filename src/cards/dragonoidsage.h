#ifndef DRAGONOIDSAGE_H
#define DRAGONOIDSAGE_H
#include "cardbase.h"
class DragonoidSage : public CardBase
{
public:
    DragonoidSage():CardBase(
        5, //card id
        3, //cost
        1, //card type (0 - spell, 1 - minion, 2 - spminion)
        3, //level
        2, //attack
        2, //defence
        "Air", //element
        "Dragonoid Sage" //name
    ) {};
    void onTurnEnd(Duel* duel, Card* card);
};

#endif
