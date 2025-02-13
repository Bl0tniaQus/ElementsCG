#ifndef FLYINGLIZARD_H
#define FLYINGLIZARD_H
#include "cardbase.h"
class FlyingLizard : public CardBase
{
public:
    FlyingLizard():CardBase(
        2016, //card id
        3, //cost
        1, //card type (0 - spell, 1 - minion, 2 - spminion)
        2, //level
        1, //attack
        1, //defence
        "Air", //element
        "Flying Lizard", //name
        "flyinglizard",
        "When this card is released as a material to summon a special minion: increase defence of that special minion by 1 and also gain 2 mana."
    ) {this->setHasOnSpecialSummonRelease(1);};
    void onSpecialSummonRelease(Duel * duel, Card * card, Card * sp_minion) override;
};

#endif
