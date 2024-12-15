#ifndef MAGNETIZE_H
#define MAGNETIZE_H
#include "cardbase.h"
class Magnetize : public CardBase
{
public:
    Magnetize():CardBase(
        27, //card id
        4, //cost
        0, //card type (0 - spell, 1 - minion, 2 - spminion)
        -1, //level
        -1, //attack
        -1, //defence
        "Earth", //element
        "Magnetize", //name
        "magnetize",
        "Target 1 earth minion you control: it gains attack equal to combined attack of all other earth minions you control until the end of the turn, also your other earth minions can't attack this turn."
    ) {this->setHasOnSpell(1);};
    bool onSpell(Duel* duel, Card* card) override;
    void onTurnEnd(Duel * duel, Card * card) override;
private:
    Card* target;
    short atkChange;

};

#endif
