#ifndef SHIELDBASH_H
#define SHIELDBASH_H
#include "cardbase.h"
class ShieldBash : public CardBase
{
public:
    ShieldBash():CardBase(
        26, //card id
        2, //cost
        0, //card type (0 - spell, 1 - minion, 2 - spminion)
        -1, //level
        -1, //attack
        -1, //defence
        "Earth", //element
        "Shield Bash", //name
        "shieldbash",
        "Target one earth minion your control: deal damage to your opponent equal to it's defence."
    ) {};
    bool onSpell(Duel* duel, Card* card) override;

};

#endif
