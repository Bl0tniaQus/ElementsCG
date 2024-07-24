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
                duel->summonFromHand(targetCard, zoneid);
                this->generateOnSummonLog(duel, card);
            }
        }
}
void CopperWorm::getOnSummonTargetList(Duel* duel, Card* card)
{
    this->cardsInHandWithTheSameName(duel, card);
}
void CopperWorm::generateOnSummonLog(Duel* duel, Card* card)
{
    std::string str = "[Copper Worm] \"Copper Worm\" summoned";
    short playerId = duel->getPlayerId(card->getOwner());
    duel->appendLog(str,playerId);
}
