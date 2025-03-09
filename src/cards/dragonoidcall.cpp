#include "dragonoidcall.h"
#include "../engine/duel.h"
#include "../engine/card.h"
#include "../engine/zone.h"
#include "../engine/bot.h"
bool DragonoidCall::onSpell(Duel* duel, Card* card)
{
    this->cardsInHandWithCommonNamePart(card->getOwner(),"Dragonoid");
    std::vector<Card*> targets(*this->getTargetList()->getTargetList());
    targets = TargetList::filterCardType(targets, 1);
    this->setTargetList(targets);
    int target = singleChoice(duel,card);
    if (target==-1) {return false;}
    else
    {
        short zoneid = duel->getEmptyMinionZone(card->getOwner());
        if (zoneid==-1) {return false;}
        else
        {
                Card* targetCard = duel->getCardFromCopyId(target);
                if (targetCard == nullptr || !this->getTargetList()->isPresent(targetCard)) {return false;}
                this->spellFromHandLog(duel,card);
                this->spellCost(card);
                duel->summonFromHand(targetCard, zoneid);
                return true;
        }
    }
}

