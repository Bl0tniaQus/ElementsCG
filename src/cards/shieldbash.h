#ifndef SHIELDBASH_H
#define SHIELDBASH_H
#include "cardbase.h"
class ShieldBash : public CardBase
{
public:
    ShieldBash():CardBase(
        26, //card id
        5, //cost
        0, //card type (0 - spell, 1 - minion, 2 - spminion)
        -1, //level
        -1, //attack
        -1, //defence
        "Earth", //element
        "Shield Bash", //name
        "shieldbash",
        ""
    ) {};
    bool onSpell(Duel* duel, Card* card) override;
    void getOnSpellTargetList(Duel* duel, Card* card) override;

};

#endif
