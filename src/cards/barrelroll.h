#ifndef BARRELROLL_H
#define BARRELROLL_H
#include "cardbase.h"
class BarrelRoll : public CardBase
{
public:
    BarrelRoll():CardBase(
        33, //card id
        2, //cost
        0, //card type (0 - spell, 1 - minion, 2 - spminion)
        -1, //level
        -1, //attack
        -1, //defence
        "Air", //element
        "Barrel Roll", //name
        "barrelroll",
        "Target 1 earth minion you control: it gains attack equal to combined attack of all other earth minions you control until the end of the turn, also your other earth minions can't attack this turn."
    ) {};
    bool onSpell(Duel* duel, Card* card) override;
    void onTurnStart(Duel * duel, Card * card) override;
private:
    Card* target;
    short playerId;

};

#endif
