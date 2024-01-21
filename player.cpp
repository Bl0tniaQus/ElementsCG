#include "player.h"
#include "card.h"
#include <iostream>
Player::Player()
{
    this->hp=30;
    this->mana=15;
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
