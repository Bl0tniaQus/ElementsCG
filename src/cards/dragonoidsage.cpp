#include "dragonoidsage.h"
#include "../engine/duel.h"
#include "../engine/card.h"
void DragonoidSage::onTurnEnd(Duel* duel, Card* card)
{
    if (duel->getPlayer(duel->getTurnPlayer())==card->getOwner())
    {
        this->effectLog(duel, card);
        card->getOwner()->changeMana(2);

    }
}
