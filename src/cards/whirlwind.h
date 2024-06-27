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
        "Whirlwind" //name
    ) {};
    bool onSpell(Duel* duel, Card* card);
    void getOnSpellTargetList(Duel* duel, Card* card);

};

#endif // WHIRLWIND_H
