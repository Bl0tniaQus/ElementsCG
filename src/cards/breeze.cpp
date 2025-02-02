#include "breeze.h"
#include "../engine/duel.h"
#include "../engine/card.h"
#include "../engine/zone.h"
#include "../engine/bot.h"
bool Breeze::onSpell(Duel* duel, Card* card)
{
        this->spellFromHandLog(duel,card);
        this->spellCost(card);
        this->minionsOnYourFieldWithSameElement(duel,card->getOwner(),"Air");
        short nt = this->getTargetList()->getTargetsNumber();
        std::vector<Card*>* cards = this->getTargetList()->getTargetList();
        for (short i=0;i<nt;i++)
        {
            if (!cards->at(i)->getIsSpellImmune())
            duel->changeStats(cards->at(i),1,0);
            else duel->appendSILog(card,cards->at(i));
        }
        card->getOwner()->changeMana(nt);
        return true;
}


