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
        4, //attack
        2, //defence
        "Air", //element
        "Young Wyvern", //name
        "youngwyvern",
        "[Any 2 air minions]"
    ) {this->setMaterialNumber(2);};
    bool specialSummon(Duel* duel, Card* card) override;
    void getFirstMaterialList(Duel * duel, Card * card) override;
    void getSecondMaterialList(Duel* duel, Card* card) override;
};

#endif
