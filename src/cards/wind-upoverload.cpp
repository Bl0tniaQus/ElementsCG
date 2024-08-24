#include "wind-upoverload.h"
#include "../engine/duel.h"
#include "../engine/card.h"
#include "../engine/zone.h"
#include "../engine/bot.h"
bool WindUpOverload::onSpell(Duel* duel, Card* card)
{
    this->target = nullptr;
    this->minionsOnYourFieldWithSameElement(duel,card,"Air");
    Card** targets = this->getTargetList()->getTargetList();
    short nt = this->getTargetList()->getTargetsNumber();
    if (nt<1) {return false;}
    short target = singleChoice(duel,card);
    if (target==-1) {return false;}
    else
    {
        this->spellFromHandLog(duel,card);
        this->spellCost(card);
        Card* targetCard = targets[target];
        short orAtk = targetCard->getOriginalAttack();
        if (!targetCard->getIsSpellImmune())
        {
            this->target = targetCard;
            duel->changeStats(targetCard,orAtk*2 - targetCard->getAttack(),0);
            duel->addTurnEndLingeringEffect(card);
        }
        else duel->appendSILog(card,targetCard);
        return true;
    }
}
void WindUpOverload::onTurnEnd(Duel* duel, Card* card)
{
    if (this->target->getPlace()==2)
    {
        this->effectLog(duel, card);
        duel->destruction(this->target);
        this->target = nullptr;
    }
}


