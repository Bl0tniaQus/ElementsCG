#include "dragonoidcall.h"
#include "../engine/duel.h"
#include "../engine/card.h"
#include "../engine/zone.h"
#include "../engine/bot.h"
bool DragonoidCall::onSpell(Duel* duel, Card* card)
{
    this->cardsInHandWithCommonNamePart(card->getOwner(),"Dragonoid");
    std::vector<Card*>* targets = this->getTargetList()->getTargetList();
    short target = singleChoice(duel,card);
    if (target==-1) {return false;}
    else
    {
        short zoneid = duel->getEmptyMinionZone(card->getOwner());
        if (zoneid==-1) {return false;}
        else
        {
                this->spellFromHandLog(duel,card);
                this->spellCost(card);
                Card* targetCard = targets->at(target);
                duel->summonFromHand(targetCard, zoneid);
                return true;
        }
    }
}

