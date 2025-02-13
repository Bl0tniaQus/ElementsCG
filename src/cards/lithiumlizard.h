#ifndef LITHIUMLIZARD_H
#define LITHIUMLIZARD_H
#include "cardbase.h"
class LithiumLizard : public CardBase
{
public:
    LithiumLizard():CardBase(
        1005, //card id
        3, //cost
        1, //card type (0 - spell, 1 - minion, 2 - spminion)
        3, //level
        2, //attack
        2, //defence
        "Earth", //element
        "Lithium Lizard", //name
        "lithiumlizard",
        "When this card is released as a material to summon a special minion: gain 4 mana."
    ) {this->setHasOnSpecialSummonRelease(1);};
    void onSpecialSummonRelease(Duel * duel, Card * card, Card * sp_minion) override;
};

#endif
