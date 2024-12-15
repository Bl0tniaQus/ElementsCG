#include "supplybaloon.h"
#include "../engine/duel.h"
#include "../engine/card.h"
void SupplyBaloon::onTurnStart(Duel* duel, Card* card)
{
    if (duel->getPlayer(duel->getTurnPlayer())==card->getOwner())
    {
        this->effectLog(duel, card);
        duel->drawCard(card->getOwner());
        duel->drawCard(card->getOwner());

    }
}