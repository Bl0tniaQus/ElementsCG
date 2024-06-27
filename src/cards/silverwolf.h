#ifndef SILVERWOLF_H
#define SILVERWOLF_H
#include "cardbase.h"
class SilverWolf : public CardBase
{
public:
    SilverWolf():CardBase(
        2, //card id
        4, //cost
        1, //card type (0 - spell, 1 - minion, 2 - spminion)
        3, //level
        5, //attack
        3, //defence
        "Earth", //element
        "Silver Wolf" //name
    ) {};
};

#endif
