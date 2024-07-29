#ifndef DRAGONOIDSTORMCHASER_H
#define DRAGONOIDSTORMCHASER_H
#include "cardbase.h"
class DragonoidStormChaser : public CardBase
{
public:
    DragonoidStormChaser():CardBase(
        19, //card id
        7, //cost
        2, //card type (0 - spell, 1 - minion, 2 - spminion)
        7, //level
        6, //attack
        4, //defence
        "Air", //element
        "Dragonoid Storm Chaser", //name
        "dragonoidstormchaser",
        "[]\n1);\n2)."
    ) {this->setMaterialNumber(2);};
    bool specialSummon(Duel* duel, Card* card) override;
    void getFirstMaterialList(Duel * duel, Card * card) override;
    void getSecondMaterialList(Duel* duel, Card* card) override;
    void onSummon(Duel* duel, Card* card) override;
};

#endif
