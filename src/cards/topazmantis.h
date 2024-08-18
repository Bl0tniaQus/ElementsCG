#ifndef TOPAZMANTIS_H
#define TOPAZMANTIS_H
#include "cardbase.h"
class TopazMantis : public CardBase
{
public:
    TopazMantis():CardBase(
        22, //card id
        7, //cost
        2, //card type (0 - spell, 1 - minion, 2 - spminion)
        5, //level
        5, //attack
        4, //defence
        "Earth", //element
        "Topaz Mantis", //name
        "topazmantis",
        "[\"Topaz Amber Fossil\" + Any earth minion]\n1) This card can attack twice;\n2) When this card is destroyed: All of your earth minions gain +2/+2 and also you draw 1 card."
    ) {this->setMaterialNumber(2);}
    bool specialSummon(Duel* duel, Card* card) override;
    void getFirstMaterialList(Duel * duel, Card * card) override;
    void getSecondMaterialList(Duel* duel, Card* card) override;
    void onSummon(Duel* duel, Card* card) override;
    void onTurnStart(Duel * duel, Card * card) override;
    void onDestroy(Duel* duel, Card* card) override;
};

#endif
