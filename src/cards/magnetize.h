#ifndef MAGNETIZE_H
#define MAGNETIZE_H
#include "cardbase.h"
class Magnetize : public CardBase
{
public:
    Magnetize():CardBase(
        27, //card id
        5, //cost
        0, //card type (0 - spell, 1 - minion, 2 - spminion)
        -1, //level
        -1, //attack
        -1, //defence
        "Earth", //element
        "Magnetize", //name
        "magnetize",
        ""
    ) {};
    bool onSpell(Duel* duel, Card* card) override;
    void getOnSpellTargetList(Duel* duel, Card* card) override;

};

#endif
