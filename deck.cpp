#include "deck.h"

Deck::Deck()
{
    this->mainDeck = new Card[7];
    mainDeck[0] = Card(1);
    mainDeck[1] = Card(2);
    mainDeck[2] = Card(4);
    mainDeck[3] = Card(3);
    mainDeck[4] = Card(1);
    mainDeck[5] = Card(2);
    mainDeck[6] = Card(2);
    this->n_cards = 7;
}
