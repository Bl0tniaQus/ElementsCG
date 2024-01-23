#include "deck.h"

Deck::Deck()
{
    this->mainDeck = new Card[7];
    mainDeck[0] = Card(4);
    mainDeck[1] = Card(4);
    mainDeck[2] = Card(4);
    mainDeck[3] = Card(4);
    mainDeck[4] = Card(4);
    mainDeck[5] = Card(4);
    mainDeck[6] = Card(4);
    this->n_cards = 7;
}
