#include "flyinglizard.h"
#include "../engine/duel.h"
#include "../engine/card.h"
void FlyingLizard::onSpecialSummonRelease(Duel* duel, Card* card, Card* sp_minion)
{
    this->effectLog(duel, card);
    duel->changeStats(sp_minion,0,1);
    card->getOwner()->changeMana(2);
}


