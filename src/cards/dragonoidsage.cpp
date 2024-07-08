#include "dragonoidsage.h"
#include "../engine/duel.h"
#include "../engine/card.h"
void DragonoidSage::onTurnEnd(Duel* duel, Card* card)
{
    if (duel->getPlayer(duel->getTurnPlayer())==card->getOwner())
    {card->getOwner()->changeMana(2);}
}
