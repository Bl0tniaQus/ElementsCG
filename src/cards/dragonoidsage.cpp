#include "dragonoidsage.h"
#include "../engine/duel.h"
#include "../engine/card.h"
void DragonoidSage::onTurnEnd(Duel* duel, Card* card)
{
    if (duel->getPlayer(duel->getTurnPlayer())==card->getOwner())
    {
        this->effectLog(duel, card);
        duel->appendLog(duel->manaChangeLog(card->getOwner(),2),duel->getPlayerId(card->getOwner()));
        card->getOwner()->changeMana(2);

    }
}
