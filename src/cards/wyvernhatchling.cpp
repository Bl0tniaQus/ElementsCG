#include "wyvernhatchling.h"
#include "../engine/duel.h"
#include "../engine/card.h"
void WyvernHatchling::onSummon(Duel* duel, Card* card)
{
    if (card->getOwner()->getDeckSize()>0)
    {
    this->effectLog(duel, card);
    duel->appendLog(duel->drawCardLog(card->getOwner(),1),duel->getLastSource());
    duel->drawCard(card->getOwner());
    }
}
