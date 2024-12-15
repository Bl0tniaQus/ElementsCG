#ifndef STEELCENTIPEDE_H
#define STEELCENTIPEDE_H
#include "cardbase.h"
class SteelCentipede : public CardBase
{
public:
    SteelCentipede():CardBase(
        21, //card id
        5, //cost
        2, //card type (0 - spell, 1 - minion, 2 - spminion)
        5, //level
        2, //attack
        2, //defence
        "Earth", //element
        "Steel Centipede", //name
        "steelcentipede",
        "[Any 2 earth minions]\n1) If this card is summoned: gain 1 barrier;\n2) At the start of each turn if this card has no barrier: gain 1 barrier."
    ) {this->setMaterialNumber(2); this->setHasOnSummon(1); this->setHasOnTurnEnd(1);}
    bool specialSummon(Duel* duel, Card* card) override;
    void getFirstMaterialList(Duel * duel, Card * card) override;
    void getSecondMaterialList(Duel* duel, Card* card) override;
    void onSummon(Duel* duel, Card* card) override;
    void onTurnStart(Duel * duel, Card * card) override;
};

#endif
