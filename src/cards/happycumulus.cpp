#include "dragonoidscout.h"
#include "../engine/duel.h"
#include "../engine/card.h"
void HappyCumulus::onSummon(Duel* duel, Card* card)
{
    short mana = card->getOwner()->getMana();
    if (mana>=15)
    {card->getOwner()->setSummonLimit(card->getOwner()->getSummonLimit()+1);}
}
