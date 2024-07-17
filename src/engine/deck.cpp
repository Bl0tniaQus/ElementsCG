#include "deck.h"
#include "card.h"
Deck::Deck()
{
    this->mainDeck = new Card[7];
    this->mainDeck[0].getValuesFromId(2);
    this->mainDeck[1].getValuesFromId(1);
    this->mainDeck[2].getValuesFromId(1);
    this->mainDeck[3].getValuesFromId(1);
    this->mainDeck[4].getValuesFromId(1);
    this->mainDeck[5].getValuesFromId(1);
    this->mainDeck[6].getValuesFromId(1);
    this->n_cards = 7;
    for (int i=0;i<this->n_cards;i++)
    {
        this->mainDeck[i].setPlace(0);
    }
    this->n_special = 1;
    this->specialDeck = new Card[1];
    this->specialDeck[0].getValuesFromId(8);
}
Deck::Deck(short deckid)
{
    if (deckid==1)
    {
        this->mainDeck = new Card[16];
        this->mainDeck[0].getValuesFromId(1);
        this->mainDeck[1].getValuesFromId(1);
        this->mainDeck[2].getValuesFromId(1);
        this->mainDeck[3].getValuesFromId(3);
        this->mainDeck[4].getValuesFromId(3);
        this->mainDeck[5].getValuesFromId(3);
        this->mainDeck[6].getValuesFromId(10);
        this->mainDeck[7].getValuesFromId(10);
        this->mainDeck[8].getValuesFromId(10);
        this->mainDeck[9].getValuesFromId(1);
        this->mainDeck[10].getValuesFromId(1);
        this->mainDeck[11].getValuesFromId(4);
        this->mainDeck[12].getValuesFromId(4);
        this->mainDeck[13].getValuesFromId(4);
        this->mainDeck[14].getValuesFromId(11);
        this->mainDeck[15].getValuesFromId(11);
        this->n_cards = 16;
        for (int i=0;i<this->n_cards;i++)
        {
            this->mainDeck[i].setPlace(0);
        }
        this->n_special = 1;
        this->specialDeck = new Card[this->n_special];
        this->specialDeck[0].getValuesFromId(8);
        for (int i=0;i<this->n_special;i++)
        {
            this->specialDeck[i].setPlace(4);
        }
    }
    if (deckid==2)
    {
        this->mainDeck = new Card[16];
        this->mainDeck[0].getValuesFromId(1);
        this->mainDeck[1].getValuesFromId(1);
        this->mainDeck[2].getValuesFromId(1);
        this->mainDeck[3].getValuesFromId(2);
        this->mainDeck[4].getValuesFromId(2);
        this->mainDeck[5].getValuesFromId(2);
        this->mainDeck[6].getValuesFromId(1);
        this->mainDeck[7].getValuesFromId(1);
        this->mainDeck[8].getValuesFromId(1);
        this->mainDeck[9].getValuesFromId(4);
        this->mainDeck[10].getValuesFromId(4);
        this->mainDeck[11].getValuesFromId(5);
        this->mainDeck[12].getValuesFromId(6);
        this->mainDeck[13].getValuesFromId(6);
        this->mainDeck[14].getValuesFromId(7);
        this->mainDeck[15].getValuesFromId(7);
        this->n_cards = 16;
        for (int i=0;i<this->n_cards;i++)
        {
            this->mainDeck[i].setPlace(0);
        }
        this->n_special = 3;
        this->specialDeck = new Card[this->n_special];
        this->specialDeck[0].getValuesFromId(8);
        this->specialDeck[1].getValuesFromId(8);
        this->specialDeck[2].getValuesFromId(9);
        for (int i=0;i<this->n_special;i++)
        {
            this->specialDeck[i].setPlace(4);
        }
    }
}
Deck::~Deck()
{
    delete[]mainDeck;
    delete[]specialDeck;
}
