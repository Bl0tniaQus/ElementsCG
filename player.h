#ifndef PLAYER_H
#define PLAYER_H
#include "spellzone.h"
#include "minionzone.h"
#include "deck.h"
class Player
{
private:
    short hp;
    short mana;
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
    SpellZone* getSpellField() {return spellField;}
    MinionZone* getMinionField() {return minionField;}
    Player* getOpponent() {return opponent;}
    void setOpponent(Player *player){this->opponent = player;}
    void summonMinion(Card *minion, short zoneid);
    short getHandSize() {return this->n_hand;}
    void setHandSize(short n) {this->n_hand=n;}
    Card* getHand() {return this->hand;}
    void setHand(Card* hand, short size);
    short getDeckSize() {return this->n_deck;}
    void setDeckSize(short n) {this->n_deck=n;}
    Card* getDeck() {return this->deck;}
    void setDeck(Card* deck, short size);
    void toHand(Card* card);
    void setDeckOwnership();
};

#endif // PLAYER_H
