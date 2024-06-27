#include "dragonoidsage.h"
#include "../duel.h"
#include "../card.h"
void DragonoidSage::onTurnEnd(Duel* duel, Card* card)
{
    if (duel->getPlayer(duel->getTurnPlayer())==card->getOwner())
    {card->getOwner()->changeMana(2);}
}
