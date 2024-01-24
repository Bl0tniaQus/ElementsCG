#ifndef PLAYER_H
#define PLAYER_H
#include "spellzone.h"
#include "minionzone.h"
#include "deck.h"
#include "effecthandler.h"
class Player
{
private:
    short hp;
    short mana;
    char name;
    EffectHandler effectHandler; //przeniesc do player
    Player *opponent;
    SpellZone spellField[5];
    MinionZone minionField[5];
    short n_hand;
    short n_deck;
    short n_servant;
    short n_graveyard;
    Card* hand;
    Card* deck;
    Card* servantDeck;
    Card* graveyard;

public:
    Player();
    void changeHp(short val);
    void changeMana(short val);
    int getMana() {return this->mana;}
    int getHp() {return this->hp;}
    void setName(char name) {this->name = name;}
    char getName() {return this->name;}
    SpellZone* getSpellField() {return spellField;}
    MinionZone* getMinionField() {return minionField;}
    Player* getOpponent() {return opponent;}
    void setOpponent(Player *player){this->opponent = player;}
    short getHandSize() {return this->n_hand;}
    void setHandSize(short n) {this->n_hand=n;}
    Card* getHand() {return this->hand;}
    void setHand(Card* hand, short size);
    short getDeckSize() {return this->n_deck;}
    void setDeckSize(short n) {this->n_deck=n;}
    Card* getDeck() {return this->deck;}
    void setDeck(Card* deck, short size);
    void setDeckOwnership();
};

#endif // PLAYER_H
