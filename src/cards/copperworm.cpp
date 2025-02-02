#include "copperworm.h"
#include "../engine/duel.h"
#include "../engine/card.h"
void CopperWorm::onSummon(Duel* duel, Card* card)
{
        this->cardsInHandWithTheSameName(card->getOwner(), card->getName());
        if (this->getTargetList()->getTargetsNumber()>0)
        {
            std::vector<Card*>* targets = this->getTargetList()->getTargetList();
            Card* targetCard = targets->at(0);
            short zoneid = duel->getEmptyMinionZone(card->getOwner());
            if (zoneid!=-1) {
                this->effectLog(duel, card);
                duel->summonFromHand(targetCard, zoneid);
            }
        }
}

