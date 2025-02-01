#include "whirlwind.h"
#include "../engine/duel.h"
#include "../engine/card.h"
#include "../engine/zone.h"
#include "../engine/bot.h"
bool Whirlwind::onSpell(Duel* duel, Card* card)
{
    this->allMinionsOnField(duel, card);
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
        duel->toHand(targetCard);
        this->setTargetList(nullptr);
        }
        else duel->appendSILog(card,targetCard);
        return true;
    }
}

