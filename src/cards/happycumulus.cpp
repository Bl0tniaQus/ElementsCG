#include "dragonoidscout.h"
#include "../engine/duel.h"
#include "../engine/card.h"
void HappyCumulus::onSummon(Duel* duel, Card* card)
{
    short mana = card->getOwner()->getMana();
    if (mana>=12)
    {
        this->effectLog(duel, card);
        card->getOwner()->setSummonLimit(card->getOwner()->getSummonLimit()+1);

    }
}
