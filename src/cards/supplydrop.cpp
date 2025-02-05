#include "supplydrop.h"
#include "../engine/duel.h"
#include "../engine/card.h"
#include "../engine/zone.h"
#include "../engine/bot.h"
bool SupplyDrop::onSpell(Duel* duel, Card* card)
{
    this->minionsOnYourFieldWithSameElement(duel,card->getOwner(),"Air");
    short n = this->getTargetList()->getTargetsNumber();
    if (n<1) {return false;}
    short lv = this->highestLevelInTargetList();
    this->minionsInHandWithMaximumLevel(card->getOwner(),lv-1);
    short nt = this->getTargetList()->getTargetsNumber();
    if (nt<1) {return false;}
    std::vector<Card*>* targets = this->getTargetList()->getTargetList();
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

