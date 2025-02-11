#include "recycle.h"
#include "../engine/duel.h"
#include "../engine/card.h"
#include "../engine/zone.h"
#include "../engine/bot.h"
bool Recycle::onSpell(Duel* duel, Card* card)
{
    this->cardsInYourGraveyardWithSameElement(card->getOwner(),"Earth");
    std::vector<Card*>* targets = this->getTargetList()->getTargetList();
    int target = singleChoice(duel,card);
    if (target==-1) {return false;}
    else
    {
        Card* targetCard = duel->getCardFromCopyId(target);
        if (targetCard == nullptr || !this->getTargetList()->isPresent(targetCard)) {return false;}
        this->spellFromHandLog(duel,card);
        this->spellCost(card);
        this->cardsInYourGraveyardWithExactName(card->getOwner(), targetCard->getName());
        std::vector<Card*> targets2 = TargetList::filterUniqueNames(*this->getTargetList()->getTargetList());
        short n = targets2.size();
        for (short i = 0; i<n; i++)
        {
            targets2[i]->getOriginalOwner()->removeFromGraveyard(targets2[i]);
            duel->toHand(targets2[i]);
        }
        return true;
    }
}


