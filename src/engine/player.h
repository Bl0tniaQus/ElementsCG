#pragma once
#ifndef PLAYER_H
#define PLAYER_H
#include <vector>
#include <string>
class Zone;
class Card;
class Bot;
class Duel;
class Player
{
private:
    short hp;
    short mana;
    std::string name;
    Player *opponent;
    Zone* minionField;
    Duel* duel;
    short summonLimit;
    Bot* bot;
    std::vector<Card*> hand;
    std::vector<Card*> deck;
    std::vector<Card*> specialDeck;
    std::vector<Card*> graveyard;
    std::vector<Card> originalDeck;
    std::vector<Card> originalSpecialDeck;

public:
    Player();
    ~Player();
    void changeHp(short val);
    void changeMana(short val);
    int getMana() {return this->mana;}
    void setMana(short mana) {this->mana = mana;}
    int getHp() {return this->hp;}
    void setHp(short hp) {this->hp = hp;}
    void setName(const std::string& name);
    void setDuel(Duel* duel) {this->duel = duel;}
    Duel* getDuel() {return this->duel;}
    std::string getName() {return this->name;}
    Zone* getMinionField() {return minionField;}
    Player* getOpponent() {return opponent;}
    void setOpponent(Player *player){this->opponent = player;}
    short getHandSize() {return this->hand.size();}
    std::vector<Card*>* getHand() {return &this->hand;}
    void setHand(std::vector<Card*>& hand);
    void addToHand(Card* card);
    void removeFromHand(Card* card);
    short getDeckSize() {return this->deck.size();}
    std::vector<Card*>* getDeck() {return &this->deck;}
    void setDeck(std::vector<Card*>& deck);
    void addToTopDeck(Card* card);
    void addToBottomDeck(Card* card);
    void addToSpecialDeck(Card* card);
    void removeFromDeck(Card* card);
    void removeFromSpecialDeck(Card* card);
    short getGraveyardSize() {return this->graveyard.size();}
    void addToGraveyard(Card* card);
    void removeFromGraveyard(Card* card);
    std::vector<Card*>* getGraveyard() {return &this->graveyard;}
    void setGraveyard(std::vector<Card*>& graveyard);
    void setOriginalDeck(std::vector<Card>& deck);
    std::vector<Card>* getOriginalDeck() {return &this->originalDeck;}
    void setSpecialDeck(std::vector<Card*>& deck);
    void setOriginalSpecialDeck(std::vector<Card>& deck);
    std::vector<Card>* getOriginalSpecialDeck() {return &this->originalSpecialDeck;}
    short getOriginalSpecialDeckSize() {return this->originalSpecialDeck.size();}
    short getOriginalDeckSize() {return this->originalDeck.size();}
    std::vector<Card*>* getSpecialDeck() {return &this->specialDeck;}
    short getSpecialDeckSize() {return this->specialDeck.size();}
    void setDeckOwnership();
    void shuffleDeck();
    short getMinionCount();
    void setBot(Bot* bot) {this->bot = bot;}
    Bot* getBot() {return this->bot;}
    void setSummonLimit(short limit) {this->summonLimit=limit;}
    short getSummonLimit() {return this->summonLimit;}
    bool checkBot() {return this->bot!=nullptr;}
};

#endif // PLAYER_H
