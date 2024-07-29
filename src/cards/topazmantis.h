#ifndef TOPAZMANTIS_H
#define TOPAZMANTIS_H
#include "cardbase.h"
class TopazMantis : public CardBase
{
public:
    TopazMantis():CardBase(
        22, //card id
        5, //cost
        2, //card type (0 - spell, 1 - minion, 2 - spminion)
        5, //level
        2, //attack
        3, //defence
        "Earth", //element
        "Topaz Mantis", //name
        "topazmantis",
        "[]\n1);\n2)."
    ) {this->setMaterialNumber(2);}
    bool specialSummon(Duel* duel, Card* card) override;
    void getFirstMaterialList(Duel * duel, Card * card) override;
    void getSecondMaterialList(Duel* duel, Card* card) override;
    void onSummon(Duel* duel, Card* card) override;
    void onTurnStart(Duel * duel, Card * card) override;
};

#endif
