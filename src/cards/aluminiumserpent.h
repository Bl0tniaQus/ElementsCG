#ifndef ALUMINIUMSERPENT_H
#define ALUMINIUMSERPENT_H
#include "cardbase.h"
class AluminiumSerpent : public CardBase
{
public:
    AluminiumSerpent():CardBase(
        17, //card id
        2, //cost
        1, //card type (0 - spell, 1 - minion, 2 - spminion)
        2, //level
        1, //attack
        1, //defence
        "Earth", //element
        "Aluminium Serpent", //name
        "aluminiumserpent",
        "Add a left-most level 2 or lower non-special earth minion from your graveyard to your hand."
    ) {};
    void onSummon(Duel* duel, Card* card) override;
    void getOnSummonTargetList(Duel* duel, Card* card) override;
};

#endif
