#ifndef DRAGONOIDWARRIOR_H
#define DRAGONOIDWARRIOR_H
#include "cardbase.h"
#include <iostream>
class DragonoidWarrior : public CardBase
{
public:
    DragonoidWarrior():CardBase(
        3, //card id
        3, //cost
        1, //card type (0 - spell, 1 - minion, 2 - spminion)
        3, //level
        3, //attack
        4, //defence
        "Air", //element
        "Dragonoid Warrior" //name
    ) {};
    void onSummon(Duel* duel, Card* card);
    void onSpell(Duel* duel, Card* card);
    void onDestroy(Duel* duel, Card* card);
    void onAttack(Duel* duel, Card* card);
    void onDefence(Duel* duel, Card* card);
    void onTurnEnd(Duel* duel, Card* card);
};

#endif
