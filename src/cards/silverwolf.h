#ifndef SILVERWOLF_H
#define SILVERWOLF_H
#include "cardbase.h"
class SilverWolf : public CardBase
{
public:
    SilverWolf():CardBase(
        1001, //card id
        3, //cost
        1, //card type (0 - spell, 1 - minion, 2 - spminion)
        3, //level
        3, //attack
        2, //defence
        "Earth", //element
        "Silver Wolf", //name
        "silverwolf",
        ""
    ) {};
};

#endif
