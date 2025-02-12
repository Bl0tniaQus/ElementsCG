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
        3, //defence
        "Air", //element
        "Wind-up Biplane", //name
        "wind-upbiplane",
        "[1 level 3 of higher air minion + 1 air or earth minion]\nWhen this card is summoned: gain +2/2 and 1 barrier - at the start of every turn lose -1/-1 stats gained by this effect."
    ) {this->setRequiredMaterialsNumber(2); this->setHasOnSummon(true); this->setHasOnTurnStart(true); this->getNumericValues()->push_back(0);};
    bool specialSummon(Duel* duel, Card* card) override;
    void getFirstMaterialList(Duel * duel, Card * card) override;
    void getSecondMaterialList(Duel* duel, Card* card) override;
    void onSummon(Duel* duel, Card* card) override;
    void onTurnStart(Duel* duel, Card* card) override;
};

#endif
