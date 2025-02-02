#include "shieldbash.h"
#include "../engine/duel.h"
#include "../engine/card.h"
#include "../engine/zone.h"
#include "../engine/bot.h"
bool ShieldBash::onSpell(Duel* duel, Card* card)
{
    this->minionsOnYourFieldWithSameElement(duel, card->getOwner(),"Earth");
    std::vector<Card*>* targets = this->getTargetList()->getTargetList();
    short target = singleChoice(duel,card);
    if (target==-1) {return false;}
    else
    {
        this->spellFromHandLog(duel,card);
        this->spellCost(card);
        Card* targetCard = targets->at(target);
        if (!targetCard->getIsSpellImmune())
        {
        short dmg = targetCard->getDefence();
        card->getOwner()->getOpponent()->changeHp(-dmg);
        }
        else duel->appendSILog(card,targetCard);
        return true;
    }
}

