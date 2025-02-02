#ifndef WINDUPBIPLANE_H
#define WINDUPBIPLANE_H
#include "cardbase.h"
class WindUpBiplane : public CardBase
{
public:
    WindUpBiplane():CardBase(
        40, //card id
        6, //cost
        2, //card type (0 - spell, 1 - minion, 2 - spminion)
        6, //level
        3, //attack
        4, //defence
        "Air", //element
        "Wind-up Biplane", //name
        "wind-upbiplane",
        "[]\n1) "
    ) {this->setRequiredMaterialsNumber(2);};
    bool specialSummon(Duel* duel, Card* card) override;
    void getFirstMaterialList(Duel * duel, Card * card) override;
    void getSecondMaterialList(Duel* duel, Card* card) override;
};

#endif
