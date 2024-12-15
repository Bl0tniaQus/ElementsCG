#ifndef TUNGSTENFIREFLY_H
#define TUNGSTENFIREFLY_H
#include "cardbase.h"
class TungstenFirefly : public CardBase
{
public:
    TungstenFirefly():CardBase(
        6, //card id
        3, //cost
        1, //card type (0 - spell, 1 - minion, 2 - spminion)
        3, //level
        0, //attack
        2, //defence
        "Earth", //element
        "Tungsten Firefly", //name
        "tungstenfirefly",
        "At the end of your turn: draw 1 card."
    ) {this->setHasOnTurnEnd(1);};
    void onTurnEnd(Duel* duel, Card* card) override;
};

#endif
