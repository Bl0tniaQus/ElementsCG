#include "earthquake.h"
#include "../engine/duel.h"
#include "../engine/card.h"
#include "../engine/zone.h"
#include "../engine/bot.h"
bool Earthquake::onSpell(Duel* duel, Card* card)
{
    this->spellFromHandLog(duel,card);
    this->spellCost(card);
    this->allMinionsOnField(duel);
    short nt = this->getTargetList()->getTargetsNumber();
    std::vector<Card*>* cards = this->getTargetList()->getTargetList();
    for (short i=0;i<nt;i++)
    {
        if (!cards->at(i)->getIsSpellImmune())
        duel->changeStats(cards->at(i),0,-cards->at(i)->getDefence());
        else duel->appendSILog(card,cards->at(i));
    }
        return true;
}

