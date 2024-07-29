#ifndef TOPAZAMBERFOSSIL_H
#define TOPAZAMBERFOSSIL_H
#include "cardbase.h"
class TopazAmberFossil : public CardBase
{
public:
    TopazAmberFossil():CardBase(
        28, //card id
        2, //cost
        1, //card type (0 - spell, 1 - minion, 2 - spminion)
        1, //level
        0, //attack
        1, //defence
        "Earth", //element
        "Topaz Amber Fossil", //name
        "topazamberfossil",
        ""
    ) {};
    void onSummon(Duel* duel, Card* card) override;
    void getOnSummonTargetList(Duel* duel, Card* card) override;
};

#endif
