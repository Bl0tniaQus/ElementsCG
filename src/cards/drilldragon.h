#ifndef DRILLDRAGON_H
#define DRILLDRAGON_H
#include "cardbase.h"
class DrillDragon : public CardBase
{
public:
    DrillDragon():CardBase(
        34, //card id
        7, //cost
        2, //card type (0 - spell, 1 - minion, 2 - spminion)
        7, //level
        5, //attack
        5, //defence
        "Air", //element
        "Drill Dragon", //name
        "drilldragon",
        "[Lv. 3 or higher air minion + Lv.3 or higher earth or air minion]\n1) When this attacks an earth minion: it gains 4 attack for that attack."
    ) {this->setRequiredMaterialsNumber(2);this->setHasOnAttack(1); this->setHasAfterAttack(1);};
    bool specialSummon(Duel* duel, Card* card) override;
    void getFirstMaterialList(Duel * duel, Card * card) override;
    void getSecondMaterialList(Duel* duel, Card* card) override;
    void onAttack(Duel* duel, Card* card, Card* target) override;
    void afterAttack(Duel* duel, Card* card, Card* target, short damage) override;
};

#endif
