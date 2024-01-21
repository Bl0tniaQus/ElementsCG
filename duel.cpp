#include "duel.h"
#include "card.h"
#include <iostream>
Duel::Duel()
{
    players[0].setOpponent(&players[1]);
    players[1].setOpponent(&players[0]);
}
void Duel::drawField(char p)
{
    std::cout<<this->getPlayer(!p)->getHp()<<"/"<<getPlayer(!p)->getMana()<<std::endl;
    for (int i=4;i>=0;i--)
    {
        std::cout<<this->getPlayer(!p)->getSpellField()[i].getUsed()<<" ";
    }
    std::cout<<std::endl;
    for (int i=4;i>=0;i--)
    {
        std::cout<<this->getPlayer(!p)->getMinionField()[i].getUsed()<<" ";
    }
    std::cout<<std::endl<<"---------"<<std::endl;
    for (int i=0;i<5;i++)
    {
        std::cout<<this->getPlayer(p)->getMinionField()[i].getUsed()<<" ";
    }
    std::cout<<std::endl;
    for (int i=0;i<5;i++)
    {
        std::cout<<this->getPlayer(p)->getSpellField()[i].getUsed()<<" ";
    }
    std::cout<<std::endl;
    std::cout<<this->getPlayer(p)->getHp()<<"/"<<getPlayer(p)->getMana()<<std::endl;
}
void Duel::combat(Card* attacker, Card* defender)
{
    short atk = attacker->getAttack();
    short def = defender->getDefence();
    short damage = 0;
    if (atk>def)
    {
        destruction(defender);
        damage = atk-def;
    }
    if (atk<def)
    {
        destruction(attacker);
        damage = def-atk;
    }

    if (atk>def){this->players[this->turnPlayer].getOpponent()->changeHp(-damage);}
    if (def>atk){this->players[this->turnPlayer].changeHp(-damage);}
    checkWinner();
}
void Duel::directAttack(Card* attacker)
{
    short damage = attacker->getAttack();
    this->players[this->turnPlayer].getOpponent()->changeHp(-damage);
    checkWinner();
}
void Duel::checkWinner()
{
    short hp1 = players[0].getHp(); short hp2 = players[1].getHp();
    if (hp1==hp2) {std::cout<<"X";}
    else if (hp1<=0) {std::cout<<"2";}
    else if (hp2<=0) {std::cout<<"1";}

}
void Duel::destruction(Card* card)
{
    card->setPlace(3);
    card->getZone()->setUsed(false);
    card->getZone()->destroyCard();
    card->setZone(nullptr);
    //card.getOwner()
}
