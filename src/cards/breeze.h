#ifndef BREEZE_H
#define BREEZE_H
#include "cardbase.h"
class Breeze : public CardBase
{
public:
    Breeze():CardBase(
        24, //card id
        5, //cost
        0, //card type (0 - spell, 1 - minion, 2 - spminion)
        -1, //level
        -1, //attack
        -1, //defence
        "Air", //element
        "Breeze", //name
        "breeze",
        ""
    ) {};
    bool onSpell(Duel* duel, Card* card) override;

};

#endif // LIGHTNING_H
