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
void BrassBeetle::onSummon(Duel* duel, Card* card)
{

}
void BrassBeetle::onTurnStart(Duel * duel, Card * card)
{

}


