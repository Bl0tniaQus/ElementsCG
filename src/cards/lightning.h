#ifndef LIGHTNING_H
#define LIGHTNING_H
#include "cardbase.h"
class Lightning : public CardBase
{
public:
    Lightning():CardBase(
        2006, //card id
        5, //cost
        0, //card type (0 - spell, 1 - minion, 2 - spminion)
        -1, //level
        -1, //attack
        -1, //defence
        "Air", //element
        "Lightning", //name
        "lightning",
        "Inflict damage to your opponent equal to ammount of mana points above 15 you have."
    ) {this->setHasOnSpell(1);};
    bool onSpell(Duel* duel, Card* card) override;

};

#endif // LIGHTNING_H
