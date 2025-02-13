#ifndef EXCAVATION_H
#define EXCAVATION_H
#include "cardbase.h"
class Excavation : public CardBase
{
public:
    Excavation():CardBase(
        1003, //card id
        3, //cost
        0, //card type (0 - spell, 1 - minion, 2 - spminion)
        -1, //level
        -1, //attack
        -1, //defence
        "Earth", //element
        "Excavation", //name
        "excavation",
        "Reveal 3 top cards from your deck, then you can target one earth card among them and add it to your hand."
    ) {this->setHasOnSpell(1);};
    bool onSpell(Duel* duel, Card* card) override;

};

#endif
