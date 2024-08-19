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
    this->minionsOnYourFieldWithSameElementAndMinimumLevel(duel,card,"Air",3);
}
void DrillDragon::getSecondMaterialList(Duel* duel, Card* card)
{
    this->minionsOnYourFieldWithOneOfTwoElementsAndMinimumLevel(duel,card,"Air","Earth",3);
}
void DrillDragon::onAttack(Duel* duel, Card* card, Card* target)
{
    this->firstEffectLog(duel,card);
    this->effectUsed = false;
    if (!card->getIsNegated()&&target!=nullptr)
    {
        if (strcmp(target->getElement(),"Earth")==0)
        {
            duel->changeStats(card,2,0);
            this->effectUsed = true;
        }

    }
}

void DrillDragon::afterAttack(Duel* duel, Card* card, Card* target, short damage)
{
    if (!card->getIsNegated()&&this->effectUsed)
    {
        duel->changeStats(card,-2,0);
        this->effectUsed = false;
    }
}


