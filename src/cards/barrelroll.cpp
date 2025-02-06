#include "barrelroll.h"
#include "../engine/duel.h"
#include "../engine/card.h"
#include "../engine/zone.h"
#include "../engine/bot.h"
bool BarrelRoll::onSpell(Duel* duel, Card* card)
{
    this->getCardTargets()->clear(); this->getNumericValues()->clear();
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
        if (!targetCard->getIsSpellImmune())
        {
            duel->changeSpellImmunity(targetCard,true);
            this->getCardTargets()->push_back(targetCard);
            duel->addTurnStartLingeringEffect(card);
            this->getNumericValues()->push_back(duel->getTurnPlayer());

        }
        else duel->appendSILog(card,targetCard);
        return true;
    }
}
void BarrelRoll::onTurnStart(Duel* duel, Card* card)
{
    std::vector<Card*>* cv = this->getCardTargets();
    std::vector<int>* nv = this->getNumericValues();
    if (cv->size() == 0 || nv->size() == 0) {return;}
    Card* target = cv->at(0);
    int playerId = nv->at(0);
    if (target->getPlace()==2&&duel->getTurnPlayer()!=playerId)
    {
        duel->addTurnStartLingeringEffect(card);
    }
    else if (target->getPlace()==2&&target->getIsSpellImmune())
    {
        this->effectLog(duel, card);
        duel->changeSpellImmunity(target, false);
        nv->clear();
        cv->clear();
    }
}


