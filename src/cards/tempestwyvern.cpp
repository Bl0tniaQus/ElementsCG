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
    this->minionsOnYourFieldWithSameElementAndMinimumLevel(duel,card,"Air",5);
}
void TempestWyvern::getSecondMaterialList(Duel* duel, Card* card)
{
    this->minionsOnYourFieldWithSameElement(duel,card,"Air");
}
void TempestWyvern::onSummon(Duel* duel, Card* card)
{
    this->firstEffectLog(duel, card);
    duel->appendLog(duel->manaChangeLog(card->getOwner(), 4), duel->getLastSource());
    card->getOwner()->changeMana(4);
}
void TempestWyvern::afterAttack(Duel* duel, Card* card, Card* target, short damage)
{
    if (damage>0) {
        this->secondEffectLog(duel, card);
        duel->appendLog(duel->manaChangeLog(card->getOwner(), damage), duel->getLastSource());
        card->getOwner()->changeMana(damage);

    }
}


