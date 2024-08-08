#include "wyvernhatchling.h"
#include "../engine/duel.h"
#include "../engine/card.h"
void WyvernHatchling::onSummon(Duel* duel, Card* card)
{
    short mana = card->getOwner()->getMana();
    if (mana>=12)
    {
        this->effectLog(duel, card);

        duel->changeLevel(card,5);

    }
}
