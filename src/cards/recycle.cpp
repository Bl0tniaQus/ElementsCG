#include "recycle.h"
#include "../engine/duel.h"
#include "../engine/card.h"
#include "../engine/zone.h"
#include "../engine/bot.h"
bool Recycle::onSpell(Duel* duel, Card* card)
{
    this->cardsInYourGraveyardWithSameElement(duel,card,"Earth");
    std::vector<Card*>* targets = this->getTargetList()->getTargetList();
    short target = singleChoice(duel,card);
    if (target==-1) {return false;}
    else
    {
        this->spellFromHandLog(duel,card);
        this->spellCost(card);
        Card* targetCard = targets->at(target);
        this->cardsInYourGraveyardWithExactName(duel, card, targetCard->getName());
        short n = this->getTargetList()->getTargetsNumber();
        std::vector<Card*>* targets2 = this->getTargetList()->getTargetList();
        for (short i = 0; i<n; i++)
        {
            targets2->at(i)->getOriginalOwner()->removeFromGraveyard(targets2->at(i));
            duel->toHand(targets2->at(i));
        }
        return true;
    }
}


