#include "dragonoidscout.h"
#include "../engine/duel.h"
#include "../engine/card.h"
void DragonoidScout::onSummon(Duel* duel, Card* card)
{
    if (card->getOwner()->getDeckSize()>0)
    {
    this->effectLog(duel, card);
    duel->drawCard(card->getOwner());
    }
}
