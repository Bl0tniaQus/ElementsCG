#ifndef DRAGONOIDSAGE_H
#define DRAGONOIDSAGE_H
#include "cardbase.h"
#include <iostream>
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
    void onSummon(Duel* duel, Card* card);
    void onSpell(Duel* duel, Card* card);
    void onDestroy(Duel* duel, Card* card);
    void onAttack(Duel* duel, Card* card);
    void onDefence(Duel* duel, Card* card);
    void onTurnEnd(Duel* duel, Card* card);
};

#endif
