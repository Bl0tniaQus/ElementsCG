#include "brassbeetle.h"
#include "../card.h"
#include "../duel.h"
#include "../zone.h"
bool BrassBeetle::specialSummon(Duel* duel, Card* card)
{
    return this->specialSummon2(duel, card);
}
void BrassBeetle::getFirstMaterialList(Duel* duel, Card* card)
{
    this->getMinionsWithSameElement(duel,card,"Earth");
}
void BrassBeetle::getSecondMaterialList(Duel* duel, Card* card)
{
    this->getMinionsWithSameElement(duel,card,"Earth");
}
void BrassBeetle::onSummon(Duel* duel, Card* card)
{
    card->setBarrier(1);
}
void BrassBeetle::onTurnStart(Duel * duel, Card * card)
{
    card->setAttacks(1);
    if (card->getBarrier()==0) {card->setBarrier(1);}
}


