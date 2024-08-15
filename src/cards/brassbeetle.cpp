#include "brassbeetle.h"
#include "../engine/card.h"
#include "../engine/duel.h"
#include "../engine/zone.h"
bool BrassBeetle::specialSummon(Duel* duel, Card* card)
{
    return this->specialSummon2(duel, card);
}
void BrassBeetle::getFirstMaterialList(Duel* duel, Card* card)
{
    this->minionsOnYourFieldWithSameElement(duel,card,"Earth");
}
void BrassBeetle::getSecondMaterialList(Duel* duel, Card* card)
{
    this->minionsOnYourFieldWithSameElement(duel,card,"Earth");
}
void BrassBeetle::afterAttack(Duel* duel, Card* card, Card* target, short damage)
{
    this->effectLog(duel, card);
    duel->changeStats(card, 1,0);
}



