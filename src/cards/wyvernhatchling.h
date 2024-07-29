#ifndef WYVERNHATCHLING_H
#define WYVERNHATCHLING_H
#include "cardbase.h"
class WyvernHatchling : public CardBase
{
public:
    WyvernHatchling():CardBase(
        25, //card id
        3, //cost
        1, //card type (0 - spell, 1 - minion, 2 - spminion)
        3, //level
        2, //attack
        1, //defence
        "Air", //element
        "Wyvern Hatchling", //name
        "wyvernhatchling",
        ""
    ) {};
    void onSummon(Duel* duel, Card* card) override;
};

#endif
