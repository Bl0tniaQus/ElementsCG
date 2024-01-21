#include "deck.h"

Deck::Deck()
{
    this->mainDeck = new Card[7];
    mainDeck[0] = Card(2);
    mainDeck[1] = Card(1);
    mainDeck[2] = Card(1);
    mainDeck[3] = Card(2);
    mainDeck[4] = Card(2);
    mainDeck[5] = Card(1);
    mainDeck[6] = Card(2);
}
