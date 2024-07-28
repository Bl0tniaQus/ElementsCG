#ifndef EXCAVATION_H
#define EXCAVATION_H
#include "cardbase.h"
class Excavation : public CardBase
{
public:
    Excavation():CardBase(
        16, //card id
        5, //cost
        0, //card type (0 - spell, 1 - minion, 2 - spminion)
        -1, //level
        -1, //attack
        -1, //defence
        "Earth", //element
        "Excavation", //name
        "excavation",
        ""
    ) {};
    bool onSpell(Duel* duel, Card* card) override;
    void getOnSpellTargetList(Duel* duel, Card* card) override;

};

#endif
