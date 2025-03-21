#ifndef WHIRLWIND_H
#define WHIRLWIND_H
#include "cardbase.h"
class Whirlwind : public CardBase
{
public:
    Whirlwind():CardBase(
        2001, //card id
        7, //cost
        0, //card type (0 - spell, 1 - minion, 2 - spminion)
        -1, //level
        -1, //attack
        -1, //defence
        "Air", //element
        "Whirlwind", //name
        "whirlwind",
        "Target 1 minion on the field: return it to it's owner's hand."
    ) {this->setHasOnSpell(1);};
    bool onSpell(Duel* duel, Card* card) override;

};

#endif // WHIRLWIND_H
