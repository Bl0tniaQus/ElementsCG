#include "zone.h"
#include "card.h"
void Zone::bindCard(Card* card)
{
    this->card = card;
    card->setZone(this);
}
void Zone::destroyCard()
{
    this->card = nullptr;
}

