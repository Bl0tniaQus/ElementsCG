#ifndef PLAYER_H
#define PLAYER_H
#include "deck.h"
#include "zone.h"
#include "effecthandler.h"
class Player
{
private:
    short hp;
    short mana;
    char name;
    EffectHandler effectHandler; //przeniesc do player
    Player *opponent;
    Zone* spellField;
    Zone* minionField;
    short n_hand;
    short n_deck;
    short n_originalDeck;
    short n_originalServantDeck;
    short n_servant;
    short n_graveyard;
    Card** hand;
    Card** deck;
    Card** servantDeck;
    Card** graveyard;
    Card* originalDeck;
    Card* originalServantDeck;

public:
    Player();
    void changeHp(short val);
    void changeMana(short val);
    int getMana() {return this->mana;}
    int getHp() {return this->hp;}
    void setName(char name) {this->name = name;}
    char getName() {return this->name;}
    Zone* getSpellField() {return spellField;}
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
    void setServantDeck(Card** deck, short size);
    void setOriginalServantDeck(Card* deck, short size);
    Card** getServantDeck() {return this->servantDeck;}
    void setDeckOwnership();
};

#endif // PLAYER_H
