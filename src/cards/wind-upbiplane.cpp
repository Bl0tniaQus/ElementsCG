#include "wind-upbiplane.h"
#include "../engine/card.h"
#include "../engine/duel.h"
#include "../engine/zone.h"
bool WindUpBiplane::specialSummon(Duel* duel, Card* card)
{
    return this->specialSummon2(duel, card);
}
void WindUpBiplane::getFirstMaterialList(Duel* duel, Card* card)
{
    this->minionsOnYourFieldWithSameElementAndMinimumLevel(duel,card->getOwner(),"Air",3);
}
void WindUpBiplane::getSecondMaterialList(Duel* duel, Card* card)
{
    this->minionsOnYourFieldWithOneOfTwoElementsAndMinimumLevel(duel,card->getOwner(),"Air","Earth",3);
}


