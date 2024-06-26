#ifndef COPPERWORM_H
#define COPPERWORM_H
#include "cardbase.h"
#include <iostream>
class CopperWorm : public CardBase
{
public:
    CopperWorm():CardBase(
        1, //card id
        1, //cost
        1, //card type (0 - spell, 1 - minion, 2 - spminion)
        1, //level
        1, //attack
        1, //defence
        "Earth", //element
        "Copper Worm" //name
    ) {};
    void onSummon(Duel* duel, Card* card);
    void onSpell(Duel* duel, Card* card);
    void onDestroy(Duel* duel, Card* card);
    void onAttack(Duel* duel, Card* card);
    void onDefence(Duel* duel, Card* card);
    void onTurnEnd(Duel* duel, Card* card);
};

#endif // COPPERWORM_H
