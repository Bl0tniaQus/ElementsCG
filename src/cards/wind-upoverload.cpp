#include "wind-upoverload.h"
#include "../engine/duel.h"
#include "../engine/card.h"
#include "../engine/zone.h"
#include "../engine/bot.h"
bool WindUpOverload::onSpell(Duel* duel, Card* card)
{
    this->getCardTargets()->clear();
    this->minionsOnYourFieldWithSameElement(duel,card->getOwner(),"Air");
    std::vector<Card*>* targets = this->getTargetList()->getTargetList();
    short nt = this->getTargetList()->getTargetsNumber();
    if (nt<1) {return false;}
    int target = singleChoice(duel,card);
    if (target==-1) {return false;}
    else
    {
        Card* targetCard = duel->getCardFromCopyId(target);
        if (targetCard == nullptr || !this->getTargetList()->isPresent(targetCard)) {return false;}
        this->spellFromHandLog(duel,card);
        this->spellCost(card);
        short orAtk = targetCard->getOriginalAttack();
        if (!targetCard->getIsSpellImmune())
        {
            this->getCardTargets()->push_back(targetCard);
            duel->changeStats(targetCard,orAtk*2 - targetCard->getAttack(),0);
            duel->addTurnEndLingeringEffect(card);
        }
        else duel->appendSILog(card,targetCard);
        return true;
    }
}
void WindUpOverload::onTurnEnd(Duel* duel, Card* card)
{
    std::vector<Card*>* cv = this->getCardTargets();
    if (cv->size()==0) {return;}
    Card* target = cv->at(0);
    if (target->getPlace()==2)
    {
        this->effectLog(duel, card);
        duel->destruction(target);
    }
    cv->clear();
}


