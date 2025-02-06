#include "wind-upcopter.h"
#include "../engine/duel.h"
#include "../engine/card.h"
void WindUpCopter::onSummon(Duel* duel, Card* card)
{
    this->getBooleanValues()->clear();
    this->getBooleanValues()->push_back(false);
    this->effectLog(duel, card);
    duel->changeStats(card,2,0);
    this->getBooleanValues()->at(0) = true;
    duel->addTurnEndLingeringEffect(card);
}
void WindUpCopter::onTurnEnd(Duel* duel, Card* card)
{
    if (this->getBooleanValues()->size() == 0) {return;}
    bool x = this->getBooleanValues()->at(0);
    if (x)
    {
        this->effectLog(duel,card);
        short a = 2 - card->getAttack();
        duel->changeStats(card,a,0);

    }
    this->getBooleanValues()->clear();
}

