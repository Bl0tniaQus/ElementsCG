#ifndef WINDUPAIRPLANE_H
#define WINDUPAIRPLANE_H
#include "cardbase.h"
class WindUpAirplane : public CardBase
{
public:
    WindUpAirplane():CardBase(
        2505, //card id
        4, //cost
        2, //card type (0 - spell, 1 - minion, 2 - spminion)
        4, //level
        2, //attack
        2, //defence
        "Air", //element
        "Wind-up Airplane", //name
        "wind-upairplane",
        "[1 air minion + 1 air or earth minion]\nWhen this card is summoned: gain +2 attack and at the start of every turn lose -1 attack gained by this effect."
    ) {this->setRequiredMaterialsNumber(2); this->setHasOnSummon(true); this->setHasOnTurnStart(true); this->getNumericValues()->push_back(0);};
    bool specialSummon(Duel* duel, Card* card) override;
    void getFirstMaterialList(Duel * duel, Card * card) override;
    void getSecondMaterialList(Duel* duel, Card* card) override;
    void onSummon(Duel* duel, Card* card) override;
    void onTurnStart(Duel* duel, Card* card) override;
};

#endif
