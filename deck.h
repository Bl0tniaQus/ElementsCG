#ifndef DECK_H
#define DECK_H
#include "card.h"

class Deck
{
private:
    Card* mainDeck;
    Card* servantDeck;
    short n_cards;
    short n_servants;
public:
    Deck();
    Card* getDeck() {return this->mainDeck;}
    short getDeckSize() {return this->n_cards;}
    Card* getServantDeck() {return this->servantDeck;}
    short getServantDeckSize() {return this->n_servants;}
};

#endif // DECK_H
