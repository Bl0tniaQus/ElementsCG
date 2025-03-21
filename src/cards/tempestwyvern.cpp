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
    this->minionsOnYourFieldWithSameElementAndMinimumLevel(duel,card->getOwner(),"Air",5);
}
void TempestWyvern::getSecondMaterialList(Duel* duel, Card* card)
{
    this->minionsOnYourFieldWithSameElement(duel,card->getOwner(),"Air");
}
void TempestWyvern::onSummon(Duel* duel, Card* card)
{
    this->firstEffectLog(duel, card);
    card->getOwner()->changeMana(6);
}
void TempestWyvern::afterAttack(Duel* duel, Card* card, Card* target, short damage)
{
    if (damage>0) {
        this->secondEffectLog(duel, card);
        card->getOwner()->changeMana(damage);

    }
}


