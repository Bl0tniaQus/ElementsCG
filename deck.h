#ifndef DECK_H
#define DECK_H
#include "card.h"

class Deck
{
private:
    Card* mainDeck;
    Card* ServantDeck;
    short n_cards;
    short n_servants;
public:
    Deck();
    Card* getDeck() {return this->mainDeck;}
};

#endif // DECK_H
