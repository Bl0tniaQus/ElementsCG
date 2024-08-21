#include "wind-upcopter.h"
#include "../engine/duel.h"
#include "../engine/card.h"
void WindUpCopter::onSummon(Duel* duel, Card* card)
{
    this->eff_used = false;
    this->effectLog(duel, card);
    duel->changeStats(card,2,0);
    this->eff_used = true;
    duel->addTurnEndLingeringEffect(card);
}
void WindUpCopter::onTurnEnd(Duel* duel, Card* card)
{
    if (this->eff_used)
    {
        this->effectLog(duel,card);
        short a = 2 - card->getAttack();
        duel->changeStats(card,a,0);

    }
    this->eff_used = false;
}

