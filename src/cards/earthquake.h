#ifndef EARTHQUAKE_H
#define EARTHQUAKE_H
#include "cardbase.h"
class Earthquake : public CardBase
{
public:
    Earthquake():CardBase(
        29, //card id
        8, //cost
        0, //card type (0 - spell, 1 - minion, 2 - spminion)
        -1, //level
        -1, //attack
        -1, //defence
        "Earth", //element
        "Earthquake", //name
        "earthquake",
        "Reduce defence of every minion on the field to 0."
    ) {this->setHasOnSpell(1);};
    bool onSpell(Duel* duel, Card* card) override;

};

#endif
