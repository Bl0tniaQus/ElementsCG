#ifndef TUNGSTENFIREFLY_H
#define TUNGSTENFIREFLY_H
#include "cardbase.h"
#include <iostream>
class TungstenFirefly : public CardBase
{
public:
    TungstenFirefly():CardBase(
        6, //card id
        3, //cost
        1, //card type (0 - spell, 1 - minion, 2 - spminion)
        3, //level
        2, //attack
        2, //defence
        "Earth", //element
        "Tungsten Firefly" //name
    ) {};
    void onSummon(Duel* duel, Card* card);
    void onSpell(Duel* duel, Card* card);
    void onDestroy(Duel* duel, Card* card);
    void onAttack(Duel* duel, Card* card);
    void onDefence(Duel* duel, Card* card);
    void onTurnEnd(Duel* duel, Card* card);
};

#endif
