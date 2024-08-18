#include "barrelroll.h"
#include "../engine/duel.h"
#include "../engine/card.h"
#include "../engine/zone.h"
#include "../engine/bot.h"
bool BarrelRoll::onSpell(Duel* duel, Card* card)
{

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
        if (!targetCard->getIsSpellImmune())
        {
            duel->changeSpellImmunity(targetCard,true);
            this->target = targetCard;
            duel->addTurnStartLingeringEffect(targetCard);
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
        duel->addTurnStartLingeringEffect(this->target);
    }
    if (this->target->getPlace()==2&&this->target->getIsSpellImmune())
    {
        duel->changeSpellImmunity(this->target, false);
    }
}


