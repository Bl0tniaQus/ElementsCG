#include "zone.h"
#include "card.h"
#include <iostream>
void Zone::bindCard(Card* card)
{

    card->setZone(this);
    this->card = card;

}
void Zone::destroyCard()
{
    this->card = nullptr;
}

