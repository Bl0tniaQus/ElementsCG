#ifndef DRAGONOIDSCOUT_H
#define DRAGONOIDSCOUT_H
#include "cardbase.h"
class DragonoidScout : public CardBase
{
public:
    DragonoidScout():CardBase(
        7, //card id
        3, //cost
        1, //card type (0 - spell, 1 - minion, 2 - spminion)
        3, //level
        3, //attack
        2, //defence
        "Air", //element
        "Dragonoid Scout" //name
    ) {};
    void onSummon(Duel* duel, Card* card);
};

#endif
