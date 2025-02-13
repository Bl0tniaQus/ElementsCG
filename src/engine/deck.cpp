#include "deck.h"
#include "card.h"
#include <iostream>
Deck::Deck()
{

}
Deck::Deck(short deckid)
{
    std::vector<short> cards;
    std::vector<short> counts;
    std::vector<short> spcards;
    if (deckid==0)
    {
        cards = {3, 18, 4, 32, 31, 33, 35, 36, 37, 38, 42, 43, 1000};
        counts = {3, 2, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 5};
        spcards = {8, 12, 9, 22, 19, 20, 21, 34, 39, 40};
        //cards = {1000};
        //counts = {10};
    }
    else if (deckid==1)
    {
        cards = {1000, 1001, 1002, 1003, 1004, 1005, 1006, 1007, 1008, 1009};
        counts = {3,3,3,3,3,3,3,3,3,3};
        spcards = {1500, 1500, 1502, 1502, 1501, 1503};
    }
    else if (deckid==2)
    {
        cards = {2000, 2001, 2002, 2003, 2004, 2005, 2006, 2007, 2008, 2009};
        counts = {3,3,3,3,3,3,3,3,3,3};
        spcards = {2501, 2501, 2502, 2503, 2500};
    }
    else if (deckid==3)
    {
        cards = {1005, 1010, 2010, 2011, 2012, 2013, 2014, 2015, 2016, 2017, 2018, 2008};
        counts = {3, 2, 3, 2, 3, 3, 3, 2, 3, 3, 3, 1};
        spcards = {2505, 2505, 2505, 2506, 2506, 2504};
    }
    this->fillDeck(cards, counts, spcards);
}
void Deck::fillDeck(std::vector<short>& cards, std::vector<short>& counts, std::vector<short>& spcards)
{
        short n_cards = 0;
        short n_special = spcards.size();
        short added = 0;
        for (short i : counts){n_cards+=i;}
        this->mainDeck = std::vector<Card>(n_cards);
        for (short i = 0; i<cards.size(); i++)
        {
            for (short j = 0; j<counts[i]; j++)
            {
                this->mainDeck[added].getValuesFromId(cards[i]);
                this->mainDeck[added].setPlace(0);
                added++;
            }
        }
        this->specialDeck = std::vector<Card>(spcards.size());
        for (int i=0;i<n_special;i++)
        {
           this->specialDeck[i].getValuesFromId(spcards[i]);
           this->specialDeck[i].setPlace(4);
        }
}
Deck::Deck(std::vector<Card>& deck, std::vector<Card>& sp_deck)
{
    short n_cards = deck.size();
    short n_special = sp_deck.size();
    this->mainDeck = std::vector<Card>(n_cards);
    this->specialDeck = std::vector<Card>(n_special);

    for (short i = 0; i<n_cards; i++)
    {
        this->mainDeck[i].getValuesFromId(deck[i].getCardId(), true);
        this->mainDeck[i].setPlace(deck[i].getPlace());
    }
    for (short i = 0; i<n_special; i++)
    {
        this->specialDeck[i].getValuesFromId(sp_deck[i].getCardId(), true);
        this->specialDeck[i].setPlace(sp_deck[i].getPlace());
    }

}
Deck::~Deck()
{

}

