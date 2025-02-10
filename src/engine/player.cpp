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
    this->summonLimit=1;
    this->bot = nullptr;
    this->hand = std::vector<Card*>(0);
    this->deck = std::vector<Card*>(0);
    this->graveyard = std::vector<Card*>(0);
    this->specialDeck = std::vector<Card*>(0);
    this->originalDeck = std::vector<Card>(0);
    this->originalSpecialDeck = std::vector<Card>(0);
    this->tokenDeck = std::vector<Card>(10);
    this->minionField = new Zone [5];
    for (int i=0;i<5;i++)
    {
        this->minionField[i].setId(i);
    }
}
void Player::setName(const std::string& name)
{
    this->name = name;
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
void Player::setHand(std::vector<Card*>& hand)
{
    this->hand = std::vector<Card*>(hand);
}
void Player::setTokenDeck(std::vector<Card>& deck)
{
    this->tokenDeck = std::vector<Card>(10);
    for (int i=0;i<10;i++)
    {
        this->tokenDeck[i].copyProperties(&deck[i]);
    }
}
void Player::setOriginalDeck(std::vector<Card>& deck)
{
    short size = deck.size();
    this->deck = std::vector<Card*>(size);
    this->originalDeck = std::vector<Card>(size);
    for (int i=0;i<size;i++)
    {
        this->originalDeck[i].copyProperties(&deck[i]);
        this->deck[i] = &this->originalDeck[i];
    }
}
void Player::setOriginalSpecialDeck(std::vector<Card>& deck)
{

    short size = deck.size();
    this->specialDeck = std::vector<Card*>(size);
    this->originalSpecialDeck = std::vector<Card>(size);
    for (int i=0;i<size;i++)
    {
        this->originalSpecialDeck[i].copyProperties(&deck[i]);
        this->specialDeck[i] = &this->originalSpecialDeck[i];
    }
}
void Player::setDeck(std::vector<Card*>& deck)
{
    this->deck = std::vector<Card*>(deck);
}
void Player::setGraveyard(std::vector<Card*>& graveyard)
{
    this->graveyard = std::vector<Card*>(graveyard);
}
void Player::setDeckOwnership()
{
    for (int i=0;i<this->originalDeck.size();i++)
    {
        this->originalDeck[i].setOwner(this);
        this->originalDeck[i].setOriginalOwner(this);
    }
    for (int i=0;i<this->deck.size();i++)
    {
        this->deck[i]->setOwner(this);
        this->deck[i]->setOriginalOwner(this);
    }
    for (int i=0;i<this->originalSpecialDeck.size();i++)
    {
        this->originalSpecialDeck[i].setOwner(this);
        this->originalSpecialDeck[i].setOriginalOwner(this);
    }
    for (int i=0;i<this->specialDeck.size();i++)
    {
        this->specialDeck[i]->setOwner(this);
        this->specialDeck[i]->setOriginalOwner(this);
    }
    for (int i=0;i<10;i++)
    {
        this->tokenDeck[i].setOwner(this);
        this->tokenDeck[i].setOriginalOwner(this);
    }
}
void Player::setSpecialDeck(std::vector<Card*>& deck)
{
    this->specialDeck = std::vector<Card*>(deck);
}
void Player::shuffleDeck()
{

    for (int i=getDeckSize()-1;i>0;i--)
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
void Player::removeFromHand(Card* card)
{
    for (int i = 0; i<this->hand.size(); i++)
    {
        if (card == this->hand[i])
            {this->hand.erase(this->hand.begin() + i); break;}
    }
}
void Player::removeFromDeck(Card* card)
{
    for (int i = 0; i<this->deck.size(); i++)
    {
        if (card == this->deck[i])
            {this->deck.erase(this->deck.begin() + i); break;}
    }
}
void Player::removeFromGraveyard(Card* card)
{
    for (int i = 0; i<this->graveyard.size(); i++)
    {
        if (card == this->graveyard[i])
            {this->graveyard.erase(this->graveyard.begin() + i); break;}
    }
}
void Player::addToHand(Card* card)
{
    this->hand.push_back(card);
    card->setPlace(1);
}
void Player::addToGraveyard(Card* card)
{
    this->graveyard.push_back(card);
    card->setPlace(3);
}
void Player::addToTopDeck(Card* card)
{
    this->deck.push_back(card);
    card->setPlace(0);
}
void Player::addToBottomDeck(Card* card)
{
    this->deck.insert(this->deck.begin(), card);
    card->setPlace(0);
}
void Player::addToSpecialDeck(Card* card)
{
    this->specialDeck.push_back(card);
    card->setPlace(4);
}
void Player::removeFromSpecialDeck(Card* card)
{
    for (int i = 0; i<this->specialDeck.size(); i++)
    {
        if (card == this->specialDeck[i])
            {this->specialDeck.erase(this->specialDeck.begin() + i); break;}
    }
}
Player::~Player()
{
    opponent = nullptr;
    delete [] minionField;
}

