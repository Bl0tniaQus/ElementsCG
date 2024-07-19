#ifndef WHIRLWIND_H
#define WHIRLWIND_H
#include "cardbase.h"
class Whirlwind : public CardBase
{
public:
    Whirlwind():CardBase(
        4, //card id
        5, //cost
        0, //card type (0 - spell, 1 - minion, 2 - spminion)
        -1, //level
        -1, //attack
        -1, //defence
        "Air", //element
        "Whirlwind", //name
        "whirlwind",
        "Whirlwind EARTH Spell (5)\nTarget 1 minion on the field: return it to it's owner's hand."
    ) {};
    bool onSpell(Duel* duel, Card* card) override;
    void getOnSpellTargetList(Duel* duel, Card* card) override;

};

#endif // WHIRLWIND_H
