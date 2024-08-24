#ifndef WINDUPOVERLOAD_H
#define WINDUPOVERLOAD_H
#include "cardbase.h"
class WindUpOverload : public CardBase
{
public:
    WindUpOverload():CardBase(
        37, //card id
        3, //cost
        0, //card type (0 - spell, 1 - minion, 2 - spminion)
        -1, //level
        -1, //attack
        -1, //defence
        "Air", //element
        "Wind-up Overload", //name
        "wind-upoverload",
        "Target 1 air minion you control: it's attack becomes double it's original attack, but it's destroyed at the end of your turn."
    ) {};
    bool onSpell(Duel* duel, Card* card) override;
    void onTurnEnd(Duel * duel, Card * card) override;
private:
    Card* target;
};

#endif
