#ifndef DRAGONOIDCALL_H
#define DRAGONOIDCALL_H
#include "cardbase.h"
class DragonoidCall : public CardBase
{
public:
    DragonoidCall():CardBase(
        14, //card id
        4, //cost
        0, //card type (0 - spell, 1 - minion, 2 - spminion)
        -1, //level
        -1, //attack
        -1, //defence
        "Air", //element
        "Dragonoid Call", //name
        "dragonoid",
        "Summon 1 \"Dragonoid\" minion from your hand"
    ) {};
    bool onSpell(Duel* duel, Card* card) override;
    void getOnSpellTargetList(Duel* duel, Card* card) override;

};

#endif
