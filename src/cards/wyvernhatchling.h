#ifndef WYVERNHATCHLING_H
#define WYVERNHATCHLING_H
#include "cardbase.h"
class WyvernHatchling : public CardBase
{
public:
    WyvernHatchling():CardBase(
        25, //card id
        1, //cost
        1, //card type (0 - spell, 1 - minion, 2 - spminion)
        1, //level
        1, //attack
        0, //defence
        "Air", //element
        "Wyvern Hatchling", //name
        "wyvernhatchling",
        "When this card is summoned if you have at least 12 mana: this card's level become 5."
    ) {this->setHasOnSummon(1);};
    void onSummon(Duel* duel, Card* card) override;
};

#endif
