#include "deck.h"

Deck::Deck()
{
    this->mainDeck = new Card[7];
    mainDeck[0] = Card(1);
    mainDeck[1] = Card(1);
    mainDeck[2] = Card(1);
    mainDeck[3] = Card(1);
    mainDeck[4] = Card(3);
    mainDeck[5] = Card(2);
    mainDeck[6] = Card(1);
    this->n_cards = 7;
    for (int i=0;i<this->n_cards;i++)
    {
        this->mainDeck[i].setPlace(0);
    }
}
