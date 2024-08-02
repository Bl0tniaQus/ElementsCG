#ifndef AMBERTREANT_H
#define AMBERTREANT_H
#include "cardbase.h"
class AmberTreant : public CardBase
{
public:
    AmberTreant():CardBase(
        20, //card id
        6, //cost
        2, //card type (0 - spell, 1 - minion, 2 - spminion)
        6, //level
        3, //attack
        3, //defence
        "Earth", //element
        "Amber Treant", //name
        "ambertreant",
        "[level 3 or higher earth minion + level 3 or lower earth minion]\n1)When this card is summoned: draw 1 \"Amber Fossil\";\n2)At the end of your turn: gain +1/+1."
    ) {this->setMaterialNumber(2);}
    bool specialSummon(Duel* duel, Card* card) override;
    void getFirstMaterialList(Duel * duel, Card * card) override;
    void getSecondMaterialList(Duel* duel, Card* card) override;
    void onSummon(Duel* duel, Card* card) override;
    void onTurnEnd(Duel * duel, Card * card) override;
    void getOnSummonTargetList(Duel * duel, Card * card) override;
};

#endif
