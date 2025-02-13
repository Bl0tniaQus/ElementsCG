#ifndef DISASSEMBLY_H
#define DISASSEMBLY_H
#include "cardbase.h"
class Disassembly : public CardBase
{
public:
    Disassembly():CardBase(
        1010, //card id
        3, //cost
        0, //card type (0 - spell, 1 - minion, 2 - spminion)
        -1, //level
        -1, //attack
        -1, //defence
        "Earth", //element
        "Disassembly", //name
        "disassembly",
        "Target one special minion you control that was special summoned using an earth minion as material: that special minion loses -2/-2 and a \"Gear token\" [L1 0/0] is summoned to your side of the field. That token's level become equal to the lowest level among earth minions used to summon targeted minion."
    ) {this->setHasOnSpell(1);};
    bool onSpell(Duel* duel, Card* card) override;

};

#endif
