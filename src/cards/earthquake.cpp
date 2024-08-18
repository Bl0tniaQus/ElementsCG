#include "earthquake.h"
#include "../engine/duel.h"
#include "../engine/card.h"
#include "../engine/zone.h"
#include "../engine/bot.h"
bool Earthquake::onSpell(Duel* duel, Card* card)
{
    this->spellFromHandLog(duel,card);
    this->spellCost(card);
    this->allMinionsOnField(duel, card);
    short nt = this->getTargetList()->getTargetsNumber();
    Card** cards = this->getTargetList()->getTargetList();
    for (short i=0;i<nt;i++)
    {
        if (!cards[i]->getIsSpellImmune())
        duel->changeStats(cards[i],0,-cards[i]->getDefence());
    }
        return true;
}

