#ifndef COPPERWORM_H
#define COPPERWORM_H
#include "cardbase.h"
class CopperWorm : public CardBase
{
public:
    CopperWorm():CardBase(
        1, //card id
        1, //cost
        1, //card type (0 - spell, 1 - minion, 2 - spminion)
        1, //level
        1, //attack
        0, //defence
        "Earth", //element
        "Copper Worm", //name
        "copperworm",
        "Copper Worm Lv1 EARTH (1)\n1/0\nIf this card is summoned: summon 1 \"Copper Worm\" from your hand."
    ) {};
    void onSummon(Duel* duel, Card* card) override;
    void getOnSummonTargetList(Duel* duel, Card* card) override;
};

#endif
