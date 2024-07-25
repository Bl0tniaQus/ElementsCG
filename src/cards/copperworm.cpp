#include "copperworm.h"
#include "../engine/duel.h"
#include "../engine/card.h"
void CopperWorm::onSummon(Duel* duel, Card* card)
{
        this->getOnSummonTargetList(duel, card);
        if (this->getTargetList()->getTargetsNumber()>0)
        {
            Card** targets = this->getTargetList()->getTargetList();
            Card* targetCard = targets[0];
            short zoneid = duel->getEmptyMinionZone(card->getOwner());
            if (zoneid!=-1) {
                this->effectLog(duel, card);
                duel->summonFromHand(targetCard, zoneid);
            }
        }
}
void CopperWorm::getOnSummonTargetList(Duel* duel, Card* card)
{
    this->cardsInHandWithTheSameName(duel, card);
}

