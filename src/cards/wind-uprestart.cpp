#include "wind-uprestart.h"
#include "../engine/duel.h"
#include "../engine/card.h"
#include "../engine/zone.h"
#include "../engine/bot.h"
bool WindUpRestart::onSpell(Duel* duel, Card* card)
{
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
            targetCard->getCardName()->onSummon(duel, targetCard);
        }
        else duel->appendSILog(card,targetCard);
        return true;
    }
}


