#include "copperworm.h"
#include "../duel.h"
#include "../card.h"
void CopperWorm::onSummon(Duel* duel, Card* card)
{
        this->getOnSummonTargetList(duel, card);
        if (this->getTargetList()->getTargetsNumber()>0)
        {
            Card** targets = this->getTargetList()->getTargetList();
            Card* targetCard = targets[0];
            duel->summonFromHand(targetCard, duel->getEmptyMinionZone(card->getOwner()));

        }
}
void CopperWorm::getOnSummonTargetList(Duel* duel, Card* card)
{
    this->cardsInHandWithTheSameName(duel, card);
}
