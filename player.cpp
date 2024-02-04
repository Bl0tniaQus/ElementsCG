#include "player.h"
#include "card.h"
#include <iostream>
Player::Player()
{
    this->hp=30;
    this->mana=15;
    this->n_hand=0;
    this->n_deck = 0;
    this->n_originalDeck=0;
    this->n_originalServantDeck=0;
    this->n_servant=0;
    this->hand = new Card* [0];
    this->deck = new Card* [0];
    this->servantDeck = new Card* [0];
    this->originalDeck = new Card [0];
    this->originalServantDeck = new Card [0];
    this->spellField = new Zone [5];
    this->minionField = new Zone [5];
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
void Player::setOriginalServantDeck(Card* deck, short size)
{
    delete[] this->originalServantDeck;
    this->originalServantDeck = deck;
    this->n_originalServantDeck = size;
    delete [] this->servantDeck;
    this->servantDeck = new Card* [size];
    for (int i=0;i<n_originalServantDeck;i++)
    {
        this->servantDeck[i] = &originalServantDeck[i];
    }
    this->n_servant = size;
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
    for (int i=0;i<this->n_servant;i++)
    {
        this->servantDeck[i]->setOwner(this);
        this->servantDeck[i]->setOriginalOwner(this);
    }
}
void Player::setServantDeck(Card** deck, short size)
{
    delete[] this->servantDeck;
    this->servantDeck = deck;
    this->n_servant = size;
}

