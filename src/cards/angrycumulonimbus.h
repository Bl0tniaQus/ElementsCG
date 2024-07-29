#ifndef ANGRYCUMULONIMBUS_H
#define ANGRYCUMULONIMBUS_H
#include "cardbase.h"
class AngryCumulonimbus : public CardBase
{
public:
    AngryCumulonimbus():CardBase(
        23, //card id
        7, //cost
        2, //card type (0 - spell, 1 - minion, 2 - spminion)
        7, //level
        6, //attack
        4, //defence
        "Air", //element
        "Angry Cumulonimbus", //name
        "angrycumulonimbus",
        "[]\n1);\n2)."
    ) {this->setMaterialNumber(2);};
    bool specialSummon(Duel* duel, Card* card) override;
    void getFirstMaterialList(Duel * duel, Card * card) override;
    void getSecondMaterialList(Duel* duel, Card* card) override;
    void onSummon(Duel* duel, Card* card) override;
};

#endif
