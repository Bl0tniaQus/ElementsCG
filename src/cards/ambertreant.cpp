#include "ambertreant.h"
#include "../engine/card.h"
#include "../engine/duel.h"
#include "../engine/zone.h"
bool AmberTreant::specialSummon(Duel* duel, Card* card)
{
    return this->specialSummon2(duel, card);
}
void AmberTreant::getFirstMaterialList(Duel* duel, Card* card)
{
    this->minionsOnYourFieldWithSameElementAndMinimumLevel(duel,card,"Earth",3);
}
void AmberTreant::getSecondMaterialList(Duel* duel, Card* card)
{
   this->minionsOnYourFieldWithSameElementAndMaximumLevel(duel,card,"Earth",3);
}
void AmberTreant::onSummon(Duel* duel, Card* card)
{
    this->getOnSummonTargetList(duel, card);
    Card** targets = this->getTargetList()->getTargetList();
    short nt = this->getTargetList()->getTargetsNumber();
    if (nt>0)
    {
        Card* t = targets[nt-1];
        this->firstEffectLog(duel, card);
        duel->searchCard(t);
    }

}
void AmberTreant::onTurnEnd(Duel* duel, Card* card)
{
    if (duel->getPlayer(duel->getTurnPlayer())==card->getOwner())
    {
        this->secondEffectLog(duel, card);
        duel->changeStats(card,0,1);
    }
}
void AmberTreant::getOnSummonTargetList(Duel* duel, Card* card)
{
    this->cardsInDeckWithCommonNamePart(duel,card,"Amber Fossil");
}




