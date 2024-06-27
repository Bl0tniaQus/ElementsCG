#include "tungstenfirefly.h"
#include "../duel.h"
#include "../card.h"
void TungstenFirefly::onTurnEnd(Duel* duel, Card* card)
{
    if (duel->getPlayer(duel->getTurnPlayer())==card->getOwner())
    { duel->drawCard(card->getOwner());}
}
