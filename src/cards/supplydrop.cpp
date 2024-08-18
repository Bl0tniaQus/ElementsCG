#include "supplydrop.h"
#include "../engine/duel.h"
#include "../engine/card.h"
#include "../engine/zone.h"
#include "../engine/bot.h"
bool SupplyDrop::onSpell(Duel* duel, Card* card)
{
    this->minionsOnYourFieldWithSameElement(duel,card,"Air");
    short n = this->getTargetList()->getTargetsNumber();
    if (n<1) {return false;}
    short lv = this->highestLevelInTargetList();
    this->minionsInHandWithMaximumLevel(duel,card,lv-1);
    short nt = this->getTargetList()->getTargetsNumber();
    if (nt<1) {return false;}
    Card** targets = this->getTargetList()->getTargetList();
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
                Card* targetCard = targets[target];
                duel->summonFromHand(targetCard, zoneid);
                return true;
        }
    }
    this->setTargetList(nullptr,0);
}

