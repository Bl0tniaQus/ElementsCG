#include "dragonoidscout.h"
#include "../engine/duel.h"
#include "../engine/card.h"
void DragonoidScout::onSummon(Duel* duel, Card* card)
{
    if (card->getOwner()->getDeckSize()>0)
    {
    this->effectLog(duel, card);
    duel->appendLog(duel->drawCardLog(card->getOwner(),1),duel->getPlayerId(card->getOwner()));
    duel->drawCard(card->getOwner());
    }
}
