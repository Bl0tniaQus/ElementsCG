#include "dragonoidscout.h"
#include "../duel.h"
#include "../card.h"
void DragonoidScout::onSummon(Duel* duel, Card* card)
{
    duel->drawCard(card->getOwner());
}
