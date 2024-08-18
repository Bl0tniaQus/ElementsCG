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
    if (deckid==0)
    {
        this->n_cards = 23;
        this->mainDeck = new Card[n_cards];
        this->mainDeck[0].getValuesFromId(1);
        this->mainDeck[1].getValuesFromId(1);
        this->mainDeck[2].getValuesFromId(14);
        this->mainDeck[3].getValuesFromId(3);
        this->mainDeck[4].getValuesFromId(3);
        this->mainDeck[5].getValuesFromId(3);
        this->mainDeck[6].getValuesFromId(26);
        this->mainDeck[7].getValuesFromId(24);
        this->mainDeck[8].getValuesFromId(10);
        this->mainDeck[9].getValuesFromId(1);
        this->mainDeck[10].getValuesFromId(1);
        this->mainDeck[11].getValuesFromId(4);
        this->mainDeck[12].getValuesFromId(4);
        this->mainDeck[13].getValuesFromId(4);
        this->mainDeck[14].getValuesFromId(13);
        this->mainDeck[15].getValuesFromId(11);
        this->mainDeck[16].getValuesFromId(28);
        this->mainDeck[17].getValuesFromId(25);
        this->mainDeck[18].getValuesFromId(17);
        this->mainDeck[19].getValuesFromId(18);
        this->mainDeck[20].getValuesFromId(29);
        this->mainDeck[21].getValuesFromId(30);
        this->mainDeck[22].getValuesFromId(31);
        for (int i=0;i<this->n_cards;i++)
        {
            this->mainDeck[i].setPlace(0);
        }
        this->n_special = 7;
        this->specialDeck = new Card[this->n_special];
        this->specialDeck[0].getValuesFromId(8);
        this->specialDeck[1].getValuesFromId(12);
        this->specialDeck[2].getValuesFromId(9);
        this->specialDeck[3].getValuesFromId(22);
        this->specialDeck[4].getValuesFromId(19);
        this->specialDeck[5].getValuesFromId(20);
        this->specialDeck[6].getValuesFromId(21);
        for (int i=0;i<this->n_special;i++)
        {
            this->specialDeck[i].setPlace(4);
        }
    }
    else if (deckid==1)
    {
        this->n_cards = 30;
        this->n_special = 6;
        short cards[] = {1,2,6,29,16,17,18,30,27,28};
        short copies[] = {3,3,3,3,3,3,3,3,3,3};
        short n_uq = 10;
        short sp_cards[] {8,21,20,22};
        short sp_copies[] = {2,2,1,1};
        short n_uq_sp = 4;
        short n = 0;
        short n_sp = 0;
        this->mainDeck = new Card[n_cards];
        for (short i = 0; i < n_uq;i++)
        {
            for (short j = 0; j<copies[i];j++)
            {
                this->mainDeck[n].getValuesFromId(cards[i]);
                this->mainDeck[n].setPlace(0);
                n++;
            }
        }
        this->specialDeck = new Card[this->n_special];
        for (short i = 0; i < n_uq_sp;i++)
        {
            for (short j = 0; j<sp_copies[i];j++)
            {
                this->specialDeck[n_sp].getValuesFromId(sp_cards[i]);
                this->specialDeck[n_sp].setPlace(4);
                n_sp++;
            }
        }
    }
    else if (deckid==2)
    {
        this->n_cards = 30;
        this->n_special = 6;
        short cards[] = {3,4,5,7,10,11,13,14,24,25};
        short copies[] = {3,3,3,3,3,3,3,3,3,3};
        short n_uq = 10;
        short sp_cards[] {12,19,23,9};
        short sp_copies[] = {2,2,1,1};
        short n_uq_sp = 4;
        short n = 0;
        short n_sp = 0;
        this->mainDeck = new Card[n_cards];
        for (short i = 0; i < n_uq;i++)
        {
            for (short j = 0; j<copies[i];j++)
            {
                this->mainDeck[n].getValuesFromId(cards[i]);
                this->mainDeck[n].setPlace(0);
                n++;
            }
        }
        this->specialDeck = new Card[this->n_special];
        for (short i = 0; i < n_uq_sp;i++)
        {
            for (short j = 0; j<sp_copies[i];j++)
            {
                this->specialDeck[n_sp].getValuesFromId(sp_cards[i]);
                this->specialDeck[n_sp].setPlace(4);
                n_sp++;
            }
        }

    }
}
Deck::~Deck()
{
    delete[]mainDeck;
    delete[]specialDeck;
}
