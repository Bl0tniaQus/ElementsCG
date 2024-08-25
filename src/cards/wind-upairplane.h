#ifndef WINDUPAIRPLANE_H
#define WINDUPAIRPLANE_H
#include "cardbase.h"
class WindUpAirplane : public CardBase
{
public:
    WindUpAirplane():CardBase(
        39, //card id
        4, //cost
        2, //card type (0 - spell, 1 - minion, 2 - spminion)
        4, //level
        2, //attack
        2, //defence
        "Air", //element
        "Wind-up Airplane", //name
        "wind-upairplane",
        "[]\n1) "
    ) {this->setMaterialNumber(2);};
    bool specialSummon(Duel* duel, Card* card) override;
    void getFirstMaterialList(Duel * duel, Card * card) override;
    void getSecondMaterialList(Duel* duel, Card* card) override;
};

#endif
