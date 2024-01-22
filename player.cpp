#include "player.h"
#include "card.h"
#include <iostream>
Player::Player()
{
    this->hp=30;
    this->mana=15;
    this->n_hand=0;
    this->n_deck = 0;
    this->hand = new Card [0];
    this->deck = new Card [0];
}
void Player::changeHp(short val)
{
    this->hp = this->hp + val;
}
void Player::changeMana(short val)
{
    this->mana = this->mana + val;
}
void Player::summonMinion(Card* minion, short zoneid)
{
    short cost = minion->getCost();
    if ((minion->getCardType()>0)&&(minion->getPlace()==1)&&(cost<=this->mana))
    {
        this->minionField[zoneid].bindCard(minion);
        this->minionField[zoneid].setUsed(true);
        this->mana-=cost;
    }
}
void Player::setHand(Card* hand, short size)
{
    delete[] this->hand;
    this->hand = hand;
    this->n_hand = size;
}
void Player::setDeck(Card* deck, short size)
{
    delete[] this->deck;
    this->deck = deck;
    this->n_deck = size;
}
void Player::setDeckOwnership()
{
    for (int i=0;i<this->n_deck;i++)
    {
        this->deck[i].setOwner(this);
    }
}
void Player::onSpell(Card* card)
{
short id = card->getCardId();
switch (id)
{
if (id==4)
{

}
}
}
void Player::setTargetList(Card* targets, short n_targets)
{
    this->targetList.setTargetList(targets);
    this->targetList.setTargetNumber(n_targets);

}
void Player::generateTargetList()
{
    short n_targets=0;
    Card* targets = new Card [n_targets];

    //any monster on field
    for (int i=0;i<5;i++)
    {
        if (i==0) {}
        Card *card = this->getOpponent()->getMinionField()[i].getCard();

        if (card!=nullptr)
        {
        n_targets++;
        Card *newtargets = new Card [n_targets];
        if (n_targets>1) {
            for (int j=0;j<n_targets;j++)
            {

                newtargets[j] = targets[j];

            }
            newtargets[n_targets-1] = *card;
            delete [] targets;
            targets = newtargets;
        } else {newtargets[0]=*card; targets = newtargets;}
        }
    }
    for (int i=0;i<5;i++)
    {
        Card *card = this->getMinionField()[i].getCard();
        if (card!=nullptr)
        {
        n_targets++;
        Card *newtargets = new Card [n_targets];
        if (n_targets>1) {
            for (int j=0;j<n_targets;j++)
            {

                newtargets[j] = targets[j];

            }
            newtargets[n_targets-1] = *card;
            delete [] targets;
            targets = newtargets;
        } else {newtargets[0]=*card; targets = newtargets;}
        }
    }

    this->setTargetList(targets,n_targets);
}
