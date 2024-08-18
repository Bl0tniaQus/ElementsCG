#ifndef SUPPLYDROP_H
#define SUPPLYDROP_H
#include "cardbase.h"
class SupplyDrop : public CardBase
{
public:
    SupplyDrop():CardBase(
        31, //card id
        3, //cost
        0, //card type (0 - spell, 1 - minion, 2 - spminion)
        -1, //level
        -1, //attack
        -1, //defence
        "Air", //element
        "Supply Drop", //name
        "supplydrop",
        "Summon 1 minion from your hand whose level is lower than the highest level among air minions you control."
    ) {};
    bool onSpell(Duel* duel, Card* card) override;

};

#endif
