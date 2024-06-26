#include "copperworm.h"
#include "../duel.h"
#include "../card.h"
void CopperWorm::onSummon(Duel* duel, Card* card)
{
bool usable = duel->checkEffectRequirements(card);
        if (usable)
        {
            Card** targets = duel->getTargetListDuel()->getTargetList();
            Card* targetCard = targets[0];
            duel->summonFromHand(targetCard, duel->getEmptyMinionZone(card->getOwner()));
        }
}
void CopperWorm::onSpell(Duel* duel, Card* card) {}
void CopperWorm::onDestroy(Duel* duel, Card* card) {}
void CopperWorm::onAttack(Duel* duel, Card* card) {}
void CopperWorm::onDefence(Duel* duel, Card* card) {}
void CopperWorm::onTurnEnd(Duel* duel, Card* card) {}
