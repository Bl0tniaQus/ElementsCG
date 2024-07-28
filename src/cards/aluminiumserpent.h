#ifndef ALUMINIUMSERPENT_H
#define ALUMINIUMSERPENT_H
#include "cardbase.h"
class AluminiumSerpent : public CardBase
{
public:
    AluminiumSerpent():CardBase(
        17, //card id
        1, //cost
        1, //card type (0 - spell, 1 - minion, 2 - spminion)
        1, //level
        0, //attack
        0, //defence
        "Earth", //element
        "Aluminium Serpent", //name
        "aluminiumserpent",
        ""
    ) {};
    void onSummon(Duel* duel, Card* card) override;
    void getOnSummonTargetList(Duel* duel, Card* card) override;
};

#endif
