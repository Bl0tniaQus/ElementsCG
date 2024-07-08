#include "tempestwyvern.h"
#include "../engine/card.h"
#include "../engine/duel.h"
#include "../engine/zone.h"
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
    card->getOwner()->changeMana(4);
}
void TempestWyvern::afterAttack(Duel* duel, Card* card, Card* target, short damage)
{
    if (damage>0) {card->getOwner()->changeMana(damage);}
}


