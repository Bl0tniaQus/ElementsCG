#ifndef LITHIUMLIZARD_H
#define LITHIUMLIZARD_H
#include "cardbase.h"
class LithiumLizard : public CardBase
{
public:
    LithiumLizard():CardBase(
        18, //card id
        1, //cost
        1, //card type (0 - spell, 1 - minion, 2 - spminion)
        1, //level
        0, //attack
        0, //defence
        "Earth", //element
        "Lithium Lizard", //name
        "lithiumlizard",
        ""
    ) {};
    void onSummon(Duel* duel, Card* card) override;
    void getOnSummonTargetList(Duel* duel, Card* card) override;
};

#endif
