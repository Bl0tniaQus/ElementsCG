#include "tempestwyvern.h"
#include "../card.h"
#include "../duel.h"
#include "../zone.h"
bool TempestWyvern::specialSummon(Duel* duel, Card* card)
{
    return this->specialSummon2(duel, card);
}
void TempestWyvern::getFirstMaterialList(Duel* duel, Card* card)
{
    this->getMinionsWithSameElementAndMinimumLevel(duel,card,"Air",3);
}
void TempestWyvern::getSecondMaterialList(Duel* duel, Card* card)
{
    this->getMinionsWithSameElementAndMinimumLevel(duel,card,"Air",3);
}
void TempestWyvern::onSummon(Duel* duel, Card* card)
{
    card->getOwner()->changeMana(6);
}
void TempestWyvern::afterAttack(Duel* duel, Card* card, Card* target, short damage)
{
    card->getOwner()->changeMana(damage);
}


