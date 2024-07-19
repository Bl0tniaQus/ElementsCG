#ifndef HAPPYCUMULUS_H
#define HAPPYCUMULUS_H
#include "cardbase.h"
class HappyCumulus : public CardBase
{
public:
    HappyCumulus():CardBase(
        10, //card id
        2, //cost
        1, //card type (0 - spell, 1 - minion, 2 - spminion)
        2, //level
        0, //attack
        1, //defence
        "Air", //element
        "Happy Cumulus", //name
        "happycumulus",
        ""
    ) {};
    void onSummon(Duel* duel, Card* card) override;
};

#endif
