#include "tungstenfirefly.h"
#include "../engine/duel.h"
#include "../engine/card.h"
void TungstenFirefly::onTurnEnd(Duel* duel, Card* card)
{
    if (duel->getPlayer(duel->getTurnPlayer())==card->getOwner()&&card->getOwner()->getDeckSize()>0)
    {
        this->effectLog(duel, card);
        duel->drawCard(card->getOwner());

    }
}
