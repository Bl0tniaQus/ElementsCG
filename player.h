#ifndef PLAYER_H
#define PLAYER_H
#include "deck.h"
#include "zone.h"
#include "bot.h"
#include "effecthandler.h"
class Player
{
private:
    short hp;
    short mana;
    char name;
    EffectHandler effectHandler; //przeniesc do player
    Player *opponent;
    Zone* minionField;
    short n_hand;
    short n_deck;
    short n_originalDeck;
    short n_originalSpecialDeck;
    short n_special;
    short n_graveyard;
    short summonLimit;
    Bot* bot;
    Card** hand;
    Card** deck;
    Card** specialDeck;
    Card** graveyard;
    Card* originalDeck;
    Card* originalSpecialDeck;

public:
    Player();
    void changeHp(short val);
    void changeMana(short val);
    int getMana() {return this->mana;}
    int getHp() {return this->hp;}
    void setName(char name) {this->name = name;}
    char getName() {return this->name;}
    Zone* getMinionField() {return minionField;}
    Player* getOpponent() {return opponent;}
    void setOpponent(Player *player){this->opponent = player;}
    short getHandSize() {return this->n_hand;}
    void setHandSize(short n) {this->n_hand=n;}
    Card** getHand() {return this->hand;}
    void setHand(Card** hand, short size);
    short getDeckSize() {return this->n_deck;}
    void setDeckSize(short n) {this->n_deck=n;}
    Card** getDeck() {return this->deck;}
    void setDeck(Card** deck, short size);
    short getGraveyardSize() {return this->n_graveyard;}
    void setGraveyardSize(short n) {this->n_graveyard=n;}
    Card** getGraveyard() {return this->graveyard;}
    void setGraveyard(Card** graveyard, short size);
    void setOriginalDeck(Card* deck, short size);
    Card* getOriginalDeck() {return this->originalDeck;}
    void setSpecialDeck(Card** deck, short size);
    void setOriginalSpecialDeck(Card* deck, short size);
    Card** getSpecialDeck() {return this->specialDeck;}
    short getSpecialDeckSize() {return this->n_special;}
    void setSpecialDeckSize(short n) {this->n_special=n;}
    void setDeckOwnership();
    void setBot();
    void setSummonLimit(short limit) {this->summonLimit=limit;}
    short getSummonLimit() {return this->summonLimit;}
    bool checkBot() {return this->bot!=nullptr;}
};

#endif // PLAYER_H
