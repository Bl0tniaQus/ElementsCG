#ifndef TEMPESTWYVERN_H
#define TEMPESTWYVERN_H
#include "cardbase.h"
class TempestWyvern : public CardBase
{
public:
    TempestWyvern():CardBase(
        9, //card id
        7, //cost
        2, //card type (0 - spell, 1 - minion, 2 - spminion)
        7, //level
        6, //attack
        4, //defence
        "Air", //element
        "Tempest Wyvern", //name
        "tempestwyvern"
    ) {};
    bool specialSummon(Duel* duel, Card* card) override;
    void getFirstMaterialList(Duel * duel, Card * card) override;
    void getSecondMaterialList(Duel* duel, Card* card) override;
    void onSummon(Duel* duel, Card* card) override;
    void afterAttack(Duel* duel, Card* card, Card* target, short damage) override;
};

#endif
