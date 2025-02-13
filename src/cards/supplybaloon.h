#ifndef SUPPLYBALOON_H
#define SUPPLYBALOON_H
#include "cardbase.h"
class SupplyBaloon : public CardBase
{
public:
    SupplyBaloon():CardBase(
        2018, //card id
        4, //cost
        1, //card type (0 - spell, 1 - minion, 2 - spminion)
        4, //level
        1, //attack
        3, //defence
        "Air", //element
        "Supply Baloon", //name
        "supplybaloon",
        "At the start of your turn: draw 2 cards."
    ) {};
    void onTurnStart(Duel* duel, Card* card) override;
};

#endif
