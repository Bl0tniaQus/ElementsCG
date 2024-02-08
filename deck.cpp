#include "deck.h"

Deck::Deck()
{
    this->mainDeck = new Card[7];
    this->mainDeck[0] = Card(5);
    this->mainDeck[1] = Card(6);
    this->mainDeck[2] = Card(1);
    this->mainDeck[3] = Card(1);
    this->mainDeck[4] = Card(1);
    this->mainDeck[5] = Card(4);
    this->mainDeck[6] = Card(2);
    this->n_cards = 7;
    for (int i=0;i<this->n_cards;i++)
    {
        this->mainDeck[i].setPlace(0);
    }
    this->n_special = 1;
    this->specialDeck = new Card[1];
    this->specialDeck[0] = Card(8);
}
