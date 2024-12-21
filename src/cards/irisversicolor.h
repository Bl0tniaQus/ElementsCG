#ifndef IRISVERSICOLOR_H
#define IRISVERSICOLOR_H
#include "cardbase.h"
class IrisVersicolor : public CardBase
{
public:
    IrisVersicolor():CardBase(
        43, //card id
        3, //cost
        1, //card type (0 - spell, 1 - minion, 2 - spminion)
        3, //level
        0, //attack
        2, //defence
        "Earth", //element
        "Iris Versicolor", //name
        "irisversicolor",
        ""
    ) {};
};

#endif
