#include "youngwyvern.h"
#include "../engine/card.h"
#include "../engine/duel.h"
#include "../engine/zone.h"
bool YoungWyvern::specialSummon(Duel* duel, Card* card)
{
    return this->specialSummon2(duel, card);
}
void YoungWyvern::getFirstMaterialList(Duel* duel, Card* card)
{
    this->getMinionsWithSameElement(duel,card,"Air");
}
void YoungWyvern::getSecondMaterialList(Duel* duel, Card* card)
{
    this->getMinionsWithSameElement(duel,card,"Air");
}



