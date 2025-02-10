#ifndef GEARTOKEN_H
#define GEARTOKEN_H
#include "cardbase.h"
class GearToken : public CardBase
{
public:
    GearToken():CardBase(
        0, //card id
        0, //cost
        1, //card type (0 - spell, 1 - minion, 2 - spminion)
        1, //level
        0, //attack
        0, //defence
        "Earth", //element
        "Gear token", //name
        "geartoken",
        ""
    ) {this->setToken();};
};

#endif
