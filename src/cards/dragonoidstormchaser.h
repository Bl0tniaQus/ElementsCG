#ifndef DRAGONOIDSTORMCHASER_H
#define DRAGONOIDSTORMCHASER_H
#include "cardbase.h"
class DragonoidStormChaser : public CardBase
{
public:
    DragonoidStormChaser():CardBase(
        2502, //card id
        6, //cost
        2, //card type (0 - spell, 1 - minion, 2 - spminion)
        6, //level
        4, //attack
        3, //defence
        "Air", //element
        "Dragonoid Storm Chaser", //name
        "dragonoidstormchaser",
        "[\"Dragonoid\" minion + any air minion]\n1) When this card is summoned if you have at least 12 mana: gain +1/+1;\n2) After this card battles: gain 2 mana."
    ) {this->setRequiredMaterialsNumber(2);this->setHasOnSummon(1); this->setHasAfterAttack(1); this->setHasAfterDefence(1);};
    bool specialSummon(Duel* duel, Card* card) override;
    void getFirstMaterialList(Duel * duel, Card * card) override;
    void getSecondMaterialList(Duel* duel, Card* card) override;
    void onSummon(Duel* duel, Card* card) override;
    void afterDefence(Duel * duel, Card * card, Card * attacker, short damage) override;
    void afterAttack(Duel* duel, Card* card, Card* attacker, short damage) override;
};

#endif
