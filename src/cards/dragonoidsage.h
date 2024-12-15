#ifndef DRAGONOIDSAGE_H
#define DRAGONOIDSAGE_H
#include "cardbase.h"
class DragonoidSage : public CardBase
{
public:
    DragonoidSage():CardBase(
        5, //card id
        3, //cost
        1, //card type (0 - spell, 1 - minion, 2 - spminion)
        3, //level
        1, //attack
        1, //defence
        "Air", //element
        "Dragonoid Sage", //name
        "dragonoidsage",
        "At the end of your turn: gain 2 mana."
    ) {this->setHasOnTurnEnd(1);};
    void onTurnEnd(Duel* duel, Card* card) override;
};

#endif
