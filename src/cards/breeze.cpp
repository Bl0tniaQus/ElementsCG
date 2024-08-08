#include "breeze.h"
#include "../engine/duel.h"
#include "../engine/card.h"
#include "../engine/zone.h"
#include "../engine/bot.h"
bool Breeze::onSpell(Duel* duel, Card* card)
{
        this->spellFromHandLog(duel,card);
        this->spellCost(card);
        this->getOnSpellTargetList(duel, card);
        short nt = this->getTargetList()->getTargetsNumber();
        Card** cards = this->getTargetList()->getTargetList();
        for (short i=0;i<nt;i++)
        {
            duel->changeStats(cards[i],1,0);
        }
        card->getOwner()->changeMana(nt);
        return true;
}
void Breeze::getOnSpellTargetList(Duel* duel, Card* card)
{
        this->minionsOnYourFieldWithSameElement(duel,card,"Air");
}


