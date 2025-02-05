#include "whirlwind.h"
#include "../engine/duel.h"
#include "../engine/card.h"
#include "../engine/zone.h"
#include "../engine/bot.h"
#include <QDebug>
bool Whirlwind::onSpell(Duel* duel, Card* card)
{
    this->allMinionsOnField(duel);
    std::vector<Card*>* targets = this->getTargetList()->getTargetList();
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
        duel->toHand(targetCard);
        this->clearTargetList();
        }
        else duel->appendSILog(card,targetCard);
        return true;
    }
}

