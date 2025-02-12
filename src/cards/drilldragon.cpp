#include "drilldragon.h"
#include "../engine/card.h"
#include "../engine/duel.h"
#include "../engine/zone.h"
bool DrillDragon::specialSummon(Duel* duel, Card* card)
{
    return this->specialSummon2(duel, card);
}
void DrillDragon::getFirstMaterialList(Duel* duel, Card* card)
{
    this->minionsOnYourFieldWithSameElementAndMinimumLevel(duel,card->getOwner(),"Air",3);
}
void DrillDragon::getSecondMaterialList(Duel* duel, Card* card)
{
    this->minionsOnYourFieldWithOneOfTwoElementsAndMinimumLevel(duel,card->getOwner(),"Air","Earth",3);
}
void DrillDragon::onAttack(Duel* duel, Card* card, Card* target)
{
    this->getBooleanValues()->clear();
    if (!card->getIsNegated()&&target!=nullptr)
    {
        if (target->getElement() == "Earth")
        {
            this->firstEffectLog(duel,card);

            duel->changeStats(card,4,0);
            this->getBooleanValues()->push_back(true);
        }

    }
}

void DrillDragon::afterAttack(Duel* duel, Card* card, Card* target, short damage)
{
    if (this->getBooleanValues()->size() == 0) {return;}
    if (!card->getIsNegated()&&this->getBooleanValues()->size()==1)
    {
        this->firstEffectLog(duel,card);
        duel->changeStats(card,-4,0);
    }
    this->getBooleanValues()->clear();
}


