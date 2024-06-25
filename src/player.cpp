#include "player.h"
#include "card.h"
#include "bot.h"
#include "zone.h"
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
void Player::changeHp(short val)
{
    this->hp = this->hp + val;
}
void Player::changeMana(short val)
{
    this->mana = this->mana + val;
}
void Player::setHand(Card** hand, short size)
{
    delete[] this->hand;
    this->hand = hand;
    this->n_hand = size;
}
void Player::setOriginalDeck(Card* deck, short size)
{
    delete[] this->originalDeck;
    this->originalDeck = deck;
    this->n_originalDeck = size;
    delete [] this->deck;
    this->deck = new Card* [size];
    for (int i=0;i<n_originalDeck;i++)
    {
        this->deck[i] = &originalDeck[i];
    }
    this->n_deck = size;
}
void Player::setOriginalSpecialDeck(Card* deck, short size)
{
    delete[] this->originalSpecialDeck;
    this->originalSpecialDeck = deck;
    this->n_originalSpecialDeck = size;
    delete [] this->specialDeck;
    this->specialDeck = new Card* [size];
    for (int i=0;i<n_originalSpecialDeck;i++)
    {
        this->specialDeck[i] = &originalSpecialDeck[i];
    }
    this->n_special = size;
}
void Player::setDeck(Card** deck, short size)
{
    delete[] this->deck;
    this->deck = deck;
    this->n_deck = size;
}
void Player::setGraveyard(Card** graveyard, short size)
{
    delete[] this->graveyard;
    this->graveyard = graveyard;
    this->n_graveyard = size;
}
void Player::setDeckOwnership()
{
    for (int i=0;i<this->n_deck;i++)
    {
        this->deck[i]->setOwner(this);
        this->deck[i]->setOriginalOwner(this);
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
    this->specialDeck = deck;
    this->n_special = size;
}
void Player::setBot()
{
    this->bot = new Bot [1];
}

