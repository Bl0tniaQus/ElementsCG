#ifndef SILVERWOLF_H
#define SILVERWOLF_H
#include "cardbase.h"
class SilverWolf : public CardBase
{
public:
    SilverWolf():CardBase(
        2, //card id
        2, //cost
        1, //card type (0 - spell, 1 - minion, 2 - spminion)
        3, //level
        2, //attack
        1, //defence
        "Earth", //element
        "Silver Wolf", //name
        "silverwolf",
        ""
    ) {};
};

#endif
