#ifndef RECYCLE_H
#define RECYCLE_H
#include "cardbase.h"
class Recycle : public CardBase
{
public:
    Recycle():CardBase(
        30, //card id
        3, //cost
        0, //card type (0 - spell, 1 - minion, 2 - spminion)
        -1, //level
        -1, //attack
        -1, //defence
        "Earth", //element
        "Recycle", //name
        "recycle",
        "Target 1 earth card in your graveyard: return all cards with the same name from your graveyard to your hand."
    ) {};
    bool onSpell(Duel* duel, Card* card) override;
    void getOnSpellTargetList(Duel* duel, Card* card) override;

};

#endif
