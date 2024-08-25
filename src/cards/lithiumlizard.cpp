#include "lithiumlizard.h"
#include "../engine/duel.h"
#include "../engine/card.h"
void LithiumLizard::onSpecialSummonRelease(Duel* duel, Card* card, Card* sp_minion)
{
    this->effectLog(duel, card);
    card->getOwner()->changeMana(4);
}


