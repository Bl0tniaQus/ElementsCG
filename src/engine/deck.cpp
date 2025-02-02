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
        cards = {3, 18, 4, 32, 31, 33, 35, 36, 37, 38, 42, 43};
        counts = {3, 2, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1};
        spcards = {8, 12, 9, 22, 19, 20, 21, 34, 39, 40};
    }
    else if (deckid==1)
    {
        cards = {1,2,6,29,16,17,18,30,27,28};
        counts = {3,3,3,3,3,3,3,3,3,3};
        spcards = {8,8,21,21,20,22};
    }
    else if (deckid==2)
    {
        cards = {3,4,5,7,10,11,13,14,24,25};
        counts = {3,3,3,3,3,3,3,3,3,3};
        spcards = {12,12,19,19,23,9};
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

