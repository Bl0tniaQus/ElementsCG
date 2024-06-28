#ifndef BRASSBEETLE_H
#define BRASSBEETLE_H
#include "cardbase.h"
class BrassBeetle : public CardBase
{
public:
    BrassBeetle():CardBase(
        8, //card id
        5, //cost
        2, //card type (0 - spell, 1 - minion, 2 - spminion)
        5, //level
        2, //attack
        5, //defence
        "Earth", //element
        "Brass Beetle" //name
    ) {};
    bool specialSummon(Duel* duel, Card* card);
    void getFirstMaterialList(Duel * duel, Card * card);
    void getSecondMaterialList(Duel* duel, Card* card);
};

#endif
