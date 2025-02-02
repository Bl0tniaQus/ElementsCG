#ifndef DECK_H
#define DECK_H
#include <vector>
class Card;
class Deck
{
private:
    std::vector<Card> mainDeck;
    std::vector<Card> specialDeck;
public:
    Deck();
    ~Deck();
    Deck(short deckid);
    std::vector<Card>* getDeck() {return &this->mainDeck;}
    short getDeckSize() {return this->mainDeck.size();}
    std::vector<Card>* getSpecialDeck() {return &this->specialDeck;}
    short getSpecialDeckSize() {return this->specialDeck.size();}
    Deck(std::vector<Card>& deck, std::vector<Card>& sp_deck);
    void fillDeck(std::vector<short>& cards, std::vector<short>& counts, std::vector<short>& spcards);
};

#endif // DECK_H
