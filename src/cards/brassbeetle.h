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
        "Brass Beetle Lv5 EARTH SP\n2/3\n[2 Earth minions]\n1) If this card is summoned: gain 1 barrier;\n2) At the start of each turn, if this card has 0 barrier: gain 1 barrier."
    ) {this->setMaterialNumber(2);}
    bool specialSummon(Duel* duel, Card* card) override;
    void getFirstMaterialList(Duel * duel, Card * card) override;
    void getSecondMaterialList(Duel* duel, Card* card) override;
    void onSummon(Duel* duel, Card* card) override;
    void onTurnStart(Duel * duel, Card * card) override;
};

#endif
