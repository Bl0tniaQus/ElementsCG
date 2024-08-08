#include "player.h"
#include "card.h"
#include "bot.h"
#include "zone.h"
#include "duel.h"
#include <iostream>
Player::Player()
{
    this->hp=30;
    this->mana=15;
    this->n_hand=0;
    this->n_deck = 0;
    this->n_originalDeck=0;
    this->summonLimit=1;
    this->n_originalSpecialDeck=0;
    this->n_special=0;
    this->n_graveyard=0;
    this->bot = nullptr;
    this->hand = new Card* [0];
    this->deck = new Card* [0];
    this->name = new char[0];
    this->specialDeck = new Card* [0];
    this->originalDeck = new Card [0];
    this->originalSpecialDeck = new Card [0];
    this->minionField = new Zone [5];
    for (int i=0;i<5;i++)
    {
        this->minionField[i].setId(i);
    }
    this->graveyard = new Card* [0];
}
void Player::setName(const char* name)
{
    delete[] this->name;
    this->name = new char[strlen(name)+1];
    strcpy(this->name, name);
}

void Player::changeHp(short val)
{
    this->duel->appendLog(this->duel->lifeChangeLog(this,val),duel->getPlayerId(this));
    this->hp = this->hp + val;
    if (this->hp < 0) {this->hp = 0;}
}
void Player::changeMana(short val)
{
    this->duel->appendLog(this->duel->manaChangeLog(this,val),duel->getPlayerId(this));
    this->mana = this->mana + val;
    if (this->mana < 0) {this->mana = 0;}
}
void Player::setHand(Card** hand, short size)
{
    delete[] this->hand;
    this->hand = new Card* [size];
    if (size==1) {this->hand[0] = hand[0];}
    else{
    for (int i=0;i<size;i++)
    {
        this->hand[i] = hand[i];
    }
    }
    this->n_hand = size;
}
void Player::setOriginalDeck(Card* deck, short size)
{
    delete[] this->originalDeck;
    this->n_originalDeck = size;
    this->n_deck = size;
    this->originalDeck = new Card [size];
    delete [] this->deck;
    this->deck = new Card* [size];
    for (int i=0;i<n_originalDeck;i++)
    {
        this->originalDeck[i].copyProperties(&deck[i]);
        this->deck[i] = &this->originalDeck[i];
    }
}
void Player::setOriginalSpecialDeck(Card* deck, short size)
{
    delete [] this->originalSpecialDeck;
    delete [] this->specialDeck;
    this->n_originalSpecialDeck = size;
    this->originalSpecialDeck = new Card [size];
    this->specialDeck = new Card* [size];
    for (int i=0;i<n_originalSpecialDeck;i++)
    {
        this->originalSpecialDeck[i].copyProperties(&deck[i]);
        this->specialDeck[i] = &this->originalSpecialDeck[i];
    }
    this->n_special = size;
}
void Player::setDeck(Card** deck, short size)
{
    delete[] this->deck;
    this->deck = new Card* [size];
    if (size==1) {this->deck[0] = deck[0];}
    else{
    for (int i=0;i<size;i++)
    {
        this->deck[i] = deck[i];
    }
    }
    this->n_deck = size;
}
void Player::setGraveyard(Card** graveyard, short size)
{
    delete[] this->graveyard;
    this->graveyard = new Card* [size];
    if (size==1) {this->graveyard[0] = graveyard[0];}
    else{
    for (int i=0;i<size;i++)
    {
        this->graveyard[i] = graveyard[i];
    }
    }
    this->n_graveyard = size;
}
void Player::setDeckOwnership()
{
    for (int i=0;i<this->n_originalDeck;i++)
    {
        this->originalDeck[i].setOwner(this);
        this->originalDeck[i].setOriginalOwner(this);
    }
    for (int i=0;i<this->n_deck;i++)
    {
        this->deck[i]->setOwner(this);
        this->deck[i]->setOriginalOwner(this);
    }
    for (int i=0;i<this->n_originalSpecialDeck;i++)
    {
        this->originalSpecialDeck[i].setOwner(this);
        this->originalSpecialDeck[i].setOriginalOwner(this);
    }
    for (int i=0;i<this->n_special;i++)
    {
        this->specialDeck[i]->setOwner(this);
        this->specialDeck[i]->setOriginalOwner(this);
    }
}
void Player::setSpecialDeck(Card** deck, short size)
{
    delete[] this->specialDeck;
    this->specialDeck = new Card* [size];
    if (size==1) {this->specialDeck[0] = deck[0];}
    else{
    for (int i=0;i<size;i++)
    {
        this->specialDeck[i] = deck[i];
    }
    }
    this->n_special = size;
}
void Player::shuffleDeck()
{

    for (int i=n_deck-1;i>0;i--)
    {
        int j = rand() % (i+1);
        Card* card = this->deck[i];
        this->deck[i] = this->deck[j];
        this->deck[j] = card;
    }
}
short Player::getMinionCount()
{
    short count = 0;

    for (int i=0;i<5;i++)
    {
            if (this->minionField[i].getCard()!=nullptr)
            {
                count++;
            }
    }
    return count;
}
Player::~Player()
{
    opponent = nullptr;
    delete [] minionField;
    delete [] hand;
    delete [] deck;
    delete [] specialDeck;
    delete [] graveyard;
    delete [] originalDeck;
    delete [] originalSpecialDeck;
}

