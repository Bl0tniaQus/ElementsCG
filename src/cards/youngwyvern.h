#ifndef YOUNGWYVERN_H
#define YOUNGWYVERN_H
#include "cardbase.h"
class YoungWyvern : public CardBase
{
public:
    YoungWyvern():CardBase(
        12, //card id
        5, //cost
        2, //card type (0 - spell, 1 - minion, 2 - spminion)
        5, //level
        3, //attack
        2, //defence
        "Air", //element
        "Young Wyvern", //name
        "youngwyvern",
        "[Any 2 air minions]\nIf this card destroys other minion in battle: gain 1 mana."
    ) {this->setRequiredMaterialsNumber(2);this->setHasAfterAttack(1);};
    bool specialSummon(Duel* duel, Card* card) override;
    void getFirstMaterialList(Duel * duel, Card * card) override;
    void getSecondMaterialList(Duel* duel, Card* card) override;
    void afterAttack(Duel * duel, Card * card, Card * target, short damage) override;
};

#endif
