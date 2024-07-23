#ifndef TEMPESTWYVERN_H
#define TEMPESTWYVERN_H
#include "cardbase.h"
class TempestWyvern : public CardBase
{
public:
    TempestWyvern():CardBase(
        9, //card id
        7, //cost
        2, //card type (0 - spell, 1 - minion, 2 - spminion)
        7, //level
        6, //attack
        4, //defence
        "Air", //element
        "Tempest Wyvern", //name
        "tempestwyvern",
        "[Lv. 5 or higher air minion + any air minion]\n1)When this card is summoned: gain 4 mana;\n2)When this card attacks and inflicts damage to your opponent: gain mana equal to damage dealt."
    ) {this->setMaterialNumber(2);};
    bool specialSummon(Duel* duel, Card* card) override;
    void getFirstMaterialList(Duel * duel, Card * card) override;
    void getSecondMaterialList(Duel* duel, Card* card) override;
    void onSummon(Duel* duel, Card* card) override;
    void afterAttack(Duel* duel, Card* card, Card* target, short damage) override;
};

#endif
