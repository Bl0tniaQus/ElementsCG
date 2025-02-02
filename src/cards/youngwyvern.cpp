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
    this->minionsOnYourFieldWithSameElement(duel,card->getOwner(),"Air");
}
void YoungWyvern::getSecondMaterialList(Duel* duel, Card* card)
{
    this->minionsOnYourFieldWithSameElement(duel,card->getOwner(),"Air");
}
void YoungWyvern::afterAttack(Duel* duel, Card* card, Card* target, short damage)
{
    if (target!=nullptr&&target->getPlace()==3)
    {
        this->effectLog(duel, card);
        card->getOwner()->changeMana(1);
    }
}




