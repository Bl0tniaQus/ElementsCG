#include "tungstenfirefly.h"
#include "../engine/duel.h"
#include "../engine/card.h"
void TungstenFirefly::onTurnEnd(Duel* duel, Card* card)
{
    if (duel->getPlayer(duel->getTurnPlayer())==card->getOwner())
    { duel->drawCard(card->getOwner());}
}
