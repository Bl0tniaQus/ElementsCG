#include "deck.h"
#include "card.h"
Deck::Deck()
{
    this->mainDeck = new Card[7];
    this->mainDeck[0] = Card(1);
    this->mainDeck[1] = Card(1);
    this->mainDeck[2] = Card(1);
    this->mainDeck[3] = Card(1);
    this->mainDeck[4] = Card(1);
    this->mainDeck[5] = Card(1);
    this->mainDeck[6] = Card(1);
    this->n_cards = 7;
    for (int i=0;i<this->n_cards;i++)
    {
        this->mainDeck[i].setPlace(0);
    }
    this->n_special = 1;
    this->specialDeck = new Card[1];
    this->specialDeck[0] = Card(8);
}
Deck::Deck(short deckid)
{
    if (deckid==1)
    {
        this->mainDeck = new Card[16];
        this->mainDeck[0] = Card(1);
        this->mainDeck[1] = Card(1);
        this->mainDeck[2] = Card(1);
        this->mainDeck[3] = Card(1);
        this->mainDeck[4] = Card(3);
        this->mainDeck[5] = Card(4);
       // this->mainDeck[6] = Card(5);
        //this->mainDeck[7] = Card(6);
       // this->mainDeck[8] = Card(7);
       // this->mainDeck[9] = Card(6);
       // this->mainDeck[10] = Card(5);
       // this->mainDeck[11] = Card(4);
       // this->mainDeck[12] = Card(6);
      //  this->mainDeck[13] = Card(2);
      //  this->mainDeck[14] = Card(3);
      //  this->mainDeck[15] = Card(4);
        this->n_cards = 6;
        for (int i=0;i<this->n_cards;i++)
        {
            this->mainDeck[i].setPlace(0);
        }
        this->n_special = 2;
        this->specialDeck = new Card[this->n_special];
        this->specialDeck[0] = Card(8);
        this->specialDeck[1] = Card(9);
    }
    if (deckid==2)
    {
        this->mainDeck = new Card[16];
        this->mainDeck[0] = Card(1);
        this->mainDeck[1] = Card(1);
        this->mainDeck[2] = Card(1);
        this->mainDeck[3] = Card(4);
        this->mainDeck[4] = Card(3);
        this->mainDeck[5] = Card(4);
        //this->mainDeck[6] = Card(5);
       // this->mainDeck[7] = Card(6);
       // this->mainDeck[8] = Card(7);
       // this->mainDeck[9] = Card(6);
       // this->mainDeck[10] = Card(5);
       // this->mainDeck[11] = Card(4);
       // this->mainDeck[12] = Card(6);
       // this->mainDeck[13] = Card(2);
       // this->mainDeck[14] = Card(3);
       // this->mainDeck[15] = Card(4);
        this->n_cards = 6;
        for (int i=0;i<this->n_cards;i++)
        {
            this->mainDeck[i].setPlace(0);
        }
        this->n_special = 2;
        this->specialDeck = new Card[this->n_special];
        this->specialDeck[0] = Card(8);
        this->specialDeck[1] = Card(9);
    }
}
