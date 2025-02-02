#include "barrelroll.h"
#include "../engine/duel.h"
#include "../engine/card.h"
#include "../engine/zone.h"
#include "../engine/bot.h"
bool BarrelRoll::onSpell(Duel* duel, Card* card)
{

    this->minionsOnYourFieldWithSameElement(duel,card->getOwner(),"Air");
    std::vector<Card*>* targets = this->getTargetList()->getTargetList();
    short nt = this->getTargetList()->getTargetsNumber();
    if (nt<1) {return false;}
    short target = singleChoice(duel,card);
    if (target==-1) {return false;}
    else
    {
        this->spellFromHandLog(duel,card);
        this->spellCost(card);
        Card* targetCard = targets->at(target);
        if (!targetCard->getIsSpellImmune())
        {
            duel->changeSpellImmunity(targetCard,true);
            this->target = targetCard;
            duel->addTurnStartLingeringEffect(card);
            this->playerId = duel->getTurnPlayer();

        }
        else duel->appendSILog(card,targetCard);
        return true;
    }
}
void BarrelRoll::onTurnStart(Duel* duel, Card* card)
{
    if (this->target->getPlace()==2&&duel->getTurnPlayer()!=this->playerId)
    {
        duel->addTurnStartLingeringEffect(card);
    }
    else if (this->target->getPlace()==2&&this->target->getIsSpellImmune())
    {
        this->effectLog(duel, card);
        duel->changeSpellImmunity(this->target, false);
    }
}
short BarrelRoll::getShort(short n)
{
    return this->playerId;
}
Card * BarrelRoll::getCard(short n)
{
    return this->target;
}

void BarrelRoll::copy(Duel* duel, CardBase* c)
{
if (c->getCard(0)!=nullptr){this->target = duel->getCardFromCopyId(c->getCard(0)->getCopyId());}
this->playerId = c->getShort(0);

}


