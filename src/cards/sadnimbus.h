#ifndef SADNIMBUS_H
#define SADNIMBUS_H
#include "cardbase.h"
class SadNimbus : public CardBase
{
public:
    SadNimbus():CardBase(
        2005, //card id
        2, //cost
        1, //card type (0 - spell, 1 - minion, 2 - spminion)
        2, //level
        1, //attack
        1, //defence
        "Air", //element
        "Sad Nimbus", //name
        "sadnimbus",
        "When this card is summoned if you have at least 12 mana: summon 1 left-most \"Sad Nimbus\" from your graveyard."
    ) {this->setHasOnSummon(1);};
    void onSummon(Duel* duel, Card* card) override;

};

#endif
