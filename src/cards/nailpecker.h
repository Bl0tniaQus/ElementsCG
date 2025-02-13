#ifndef NAILPECKER_H
#define NAILPECKER_H
#include "cardbase.h"
class Nailpecker : public CardBase
{
public:
    Nailpecker():CardBase(
        2014, //card id
        2, //cost
        1, //card type (0 - spell, 1 - minion, 2 - spminion)
        2, //level
        1, //attack
        1, //defence
        "Air", //element
        "Nailpecker", //name
        "nailpecker",
        "When this card is summoned if there is an earth minion on the field: it gains 1 attack and 1 level."
    ) {this->setHasOnSummon(1);};
    void onSummon(Duel* duel, Card* card) override;
};

#endif
