#ifndef DECK_H
#define DECK_H
class Card;
class Deck
{
private:
    Card* mainDeck;
    Card* specialDeck;
    short n_cards;
    short n_special;
public:
    Deck();
    ~Deck();
    Deck(short deckid);
    Card* getDeck() {return this->mainDeck;}
    short getDeckSize() {return this->n_cards;}
    Card* getSpecialDeck() {return this->specialDeck;}
    short getSpecialDeckSize() {return this->n_special;}
    Deck(Card* deck, short n_deck, Card* sp_deck, short n_special);
};

#endif // DECK_H
