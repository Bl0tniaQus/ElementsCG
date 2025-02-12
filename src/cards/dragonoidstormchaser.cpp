#include "dragonoidstormchaser.h"
#include "../engine/card.h"
#include "../engine/duel.h"
#include "../engine/zone.h"
bool DragonoidStormChaser::specialSummon(Duel* duel, Card* card)
{
    return this->specialSummon2(duel, card);
}
void DragonoidStormChaser::getFirstMaterialList(Duel* duel, Card* card)
{
    this->minionsOnYourFieldWithCommonNamePart(duel, card->getOwner(), "Dragonoid");
}
void DragonoidStormChaser::getSecondMaterialList(Duel* duel, Card* card)
{
    this->minionsOnYourFieldWithSameElement(duel, card->getOwner(), "Air");
}
void DragonoidStormChaser::onSummon(Duel* duel, Card* card)
{
    short mana = card->getOwner()->getMana();
    if (mana>=12)
    {
        this->firstEffectLog(duel, card);
        duel->changeStats(card,1,1);

    }
}
void DragonoidStormChaser::afterAttack(Duel* duel, Card* card, Card* attacker, short damage)
{
        this->secondEffectLog(duel, card);
        card->getOwner()->changeMana(2);
}
void DragonoidStormChaser::afterDefence(Duel* duel, Card* card, Card* attacker, short damage)
{
        this->afterAttack(duel,card,nullptr,0);
}




