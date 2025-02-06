#ifndef WINDUPCOPTER_H
#define WINDUPCOPTER_H
#include "cardbase.h"
class WindUpCopter : public CardBase
{
public:
    WindUpCopter():CardBase(
        35, //card id
        4, //cost
        1, //card type (0 - spell, 1 - minion, 2 - spminion)
        4, //level
        2, //attack
        3, //defence
        "Air", //element
        "Wind-up Copter", //name
        "wind-upcopter",
        "When this card is summoned: this card's attack become 4 until end of this turn."
    ) {this->setHasOnSummon(1);};
    void onSummon(Duel* duel, Card* card) override;
    void onTurnEnd(Duel* duel, Card* card) override;
};

#endif
