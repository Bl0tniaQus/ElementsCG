#include "dragonoidscout.h"
#include "../engine/duel.h"
#include "../engine/card.h"
void DragonoidScout::onSummon(Duel* duel, Card* card)
{
    duel->drawCard(card->getOwner());
}
