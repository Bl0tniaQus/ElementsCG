#ifndef TEMPESTWYVERN_H
#define TEMPESTWYVERN_H
#include "cardbase.h"
class TempestWyvern : public CardBase
{
public:
    TempestWyvern():CardBase(
        9, //card id
        8, //cost
        2, //card type (0 - spell, 1 - minion, 2 - spminion)
        8, //level
        8, //attack
        4, //defence
        "Air", //element
        "Tempest Wyvern", //name
        "tempestwyvern",
        "[Lv. 5 or higher air minion + any air minion]\n1) When this card is summoned: gain 6 mana;\n2) When this card attacks and inflicts damage to your opponent: gain mana equal to the ammount of damage dealt."
    ) {this->setRequiredMaterialsNumber(2);this->setHasOnSummon(1); this->setHasAfterAttack(1);};
    bool specialSummon(Duel* duel, Card* card) override;
    void getFirstMaterialList(Duel * duel, Card * card) override;
    void getSecondMaterialList(Duel* duel, Card* card) override;
    void onSummon(Duel* duel, Card* card) override;
    void afterAttack(Duel* duel, Card* card, Card* target, short damage) override;
};

#endif
