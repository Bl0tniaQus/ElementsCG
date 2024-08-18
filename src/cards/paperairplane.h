#ifndef PAPERAIRPLANE_H
#define PAPERAIRPLANE_H
#include "cardbase.h"
class PaperAirplane : public CardBase
{
public:
    PaperAirplane():CardBase(
        32, //card id
        0, //cost
        1, //card type (0 - spell, 1 - minion, 2 - spminion)
        1, //level
        1, //attack
        0, //defence
        "Air", //element
        "Paper Airplane", //name
        "paperairplane",
        ""
    ) {};
};

#endif
