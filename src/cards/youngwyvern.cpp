#include "youngwyvern.h"
#include "../engine/card.h"
#include "../engine/duel.h"
#include "../engine/zone.h"
bool YoungWyvern::specialSummon(Duel* duel, Card* card)
{
    return this->specialSummon3(duel, card);
}
void YoungWyvern::getFirstMaterialList(Duel* duel, Card* card)
{
    this->minionsOnYourFieldWithSameElement(duel,card,"Air");
}
void YoungWyvern::getSecondMaterialList(Duel* duel, Card* card)
{
    this->minionsOnYourFieldWithSameElement(duel,card,"Air");
}



