#ifndef WINDURESTART_H
#define WINDURESTART_H
#include "cardbase.h"
class WindUpRestart : public CardBase
{
public:
    WindUpRestart():CardBase(
        41, //card id
        1, //cost
        0, //card type (0 - spell, 1 - minion, 2 - spminion)
        -1, //level
        -1, //attack
        -1, //defence
        "Air", //element
        "Wind-up Restart", //name
        "wind-uprestart",
        "Target 1 air minion you control that wasn't summoned this turn: trigger it's on summon effect."
    ) {this->setHasOnSpell(1);};
    bool onSpell(Duel* duel, Card* card) override;
};

#endif
