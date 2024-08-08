#ifndef BRASSBEETLE_H
#define BRASSBEETLE_H
#include "cardbase.h"
class BrassBeetle : public CardBase
{
public:
    BrassBeetle():CardBase(
        8, //card id
        5, //cost
        2, //card type (0 - spell, 1 - minion, 2 - spminion)
        5, //level
        2, //attack
        3, //defence
        "Earth", //element
        "Brass Beetle", //name
        "brassbeetle",
        "[Any 2 earth minions]\n1)\n2)"
    ) {this->setMaterialNumber(2);}
    bool specialSummon(Duel* duel, Card* card) override;
    void getFirstMaterialList(Duel * duel, Card * card) override;
    void getSecondMaterialList(Duel* duel, Card* card) override;
    void onSummon(Duel* duel, Card* card) override;
    void onTurnStart(Duel * duel, Card * card) override;
};

#endif
