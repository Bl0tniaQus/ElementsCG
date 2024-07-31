#include "breeze.h"
#include "../engine/duel.h"
#include "../engine/card.h"
#include "../engine/zone.h"
#include "../engine/bot.h"
bool Breeze::onSpell(Duel* duel, Card* card)
{
        this->secondEffectLog(duel, card);
        short nt = this->getTargetList()->getTargetsNumber();
        Card** cards = this->getTargetList()->getTargetList();
        for (short i=0;i<nt;i++)
        {
            duel->changeStats(cards[i],1,0);
        }
        duel->appendLog(duel->manaChangeLog(card->getOwner(),nt),duel->getLastSource());
        card->getOwner()->changeMana(nt);
        return true;
}
void Breeze::getOnSpellTargetList(Duel* duel, Card* card)
{
        this->minionsOnYourFieldWithAttribute(duel,card,"Air");
}


