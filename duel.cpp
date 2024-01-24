#include "duel.h"
#include "card.h"
#include <iostream>
Duel::Duel()
{
    players[0].setOpponent(&players[1]);
    players[1].setOpponent(&players[0]);
    players[0].setName('a');
    players[1].setName('b');
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
    if ((hp1<=0)&&(hp2<=0)) {std::cout<<"X";}
    else if ((hp1<=0)&&(hp2>0)) {std::cout<<"2";}
    else if ((hp2<=0)&&(hp1>0)) {std::cout<<"1";}

}
void Duel::destruction(Card* card)
{
    card->setPlace(3);
    card->getZone()->setUsed(false);
    card->getZone()->destroyCard();
    card->setZone(nullptr);
    //card.getOwner()
}
short Duel::getEmptyMinionZone(Player* player)
{
    Zone* zones = player->getMinionField();
    for (int i=0;i<5;i++)
    {
        if (zones[i].getUsed()==false) {return i;}
        std::cout<<i;
    }
    return -1;
}
void Duel::summonMinion(Card *minion, short zoneid)
{
    if ((minion->getCardType()>0)&&(minion->getPlace()==1))
    {

        minion->getOwner()->getMinionField()->bindCard(minion);
        minion->getOwner()->getMinionField()[zoneid].setUsed(true);
        this->onSummon(minion);
    }
}

void Duel::toHand(Card* card)
{
    card->setPlace(1);
    card->getZone()->setUsed(false);
    card->getZone()->destroyCard();
    card->setZone(nullptr);
    short n_hand = card->getOriginalOwner()->getHandSize();
    Card* oldHand = card->getOriginalOwner()->getHand();
    Card* newHand = new Card[n_hand+1];
    if (n_hand==1) {newHand[0] = *card;}
    else{
    for (int i=0;i<n_hand;i++)
    {
        newHand[i] = oldHand[i];
    }
    }
    newHand[n_hand] = *card;
    card->getOriginalOwner()->setHand(newHand, n_hand+1);
    card->getOriginalOwner()->setHandSize(n_hand+1);
}
void Duel::drawCard(char p)
{
    short n_deck = this->getPlayer(p)->getDeckSize();
    if (n_deck>0)
    {
        short n_hand = this->getPlayer(p)->getHandSize();
        Card* oldHand = this->getPlayer(p)->getHand();
        Card* newHand = new Card[n_hand+1];
        Card* newDeck = new Card[n_deck-1];
        Card* oldDeck = this->getPlayer(p)->getDeck();

        if (n_hand==0) {newHand[0] = oldDeck[n_deck-1];}
        else{
        for (int i=0;i<n_hand;i++)
        {
            newHand[i] = oldHand[i];
        }
        }
        oldDeck[n_deck-1].setPlace(1);
        newHand[n_hand] = oldDeck[n_deck-1];
        this->getPlayer(p)->setHand(newHand, n_hand+1);
        for (int i=0;i<n_deck-1;i++)
        {
            newDeck[i] = oldDeck[i];
        }
        this->getPlayer(p)->setHandSize(n_hand+1);
        this->getPlayer(p)->setDeckSize(n_deck-1);
        this->getPlayer(p)->setDeck(newDeck,n_deck-1);
    }


}
bool Duel::checkEffectRequirements(Card* card)
{
//any monster on field
    short id = card->getCardId();
if (id==4)
{
this->generateTargetList(card);
    if (this->targetList.getTargetsNumber()>0) {return true;}
}
return false;
}
void Duel::onSpell(Card* card)
{
short id = card->getCardId();
if (id==4) //Whirlwind
{
    bool usable = this->checkEffectRequirements(card);
    if (usable)
    {
        Card* targets = this->targetList.getTargetList();
        int target;
        for (int i=0;i<this->targetList.getTargetsNumber();i++)
        {
            std::cout<<i<<" - "<<targets[i].getName()<<std::endl;
        }
        std::cout<<"Target: ";
        std::cin>>target;
        card->getOwner()->changeMana(-card->getCost());
        Card* targetCard = &targets[target];
        this->toHand(targetCard);
    }
}
}

void Duel::setTargetList(Card* targets, short n_targets)
{
    this->targetList.setTargetList(targets);
    this->targetList.setTargetNumber(n_targets);

}

void Duel::generateTargetList(Card* effect)
{
    short n_targets=0;
    Card* targets = new Card [n_targets];
    short effectId = effect->getCardId();
    //any monster on field
    if (effectId==4)
    {
        for (int i=0;i<5;i++)
        {
            Card *card = this->players[getTurnPlayer()].getOpponent()->getMinionField()[i].getCard();

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
            Card *card = this->players[getTurnPlayer()].getMinionField()[i].getCard();
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
    }
    //Monster in hand with the same name
    else if (effectId==1)
    {
        for (int i=0;i<effect->getOwner()->getHandSize();i++)
        {
            Card *card = &effect->getOwner()->getHand()[i];

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
    }

    this->setTargetList(targets,n_targets);
}
void Duel::playFromHand(Card* card)
{
    char type = card->getCardType();
    short cost = card->getCost();
    if ((cost<=card->getOwner()->getMana())||(card->getPlace()==1))
    {
        if (type='0')
        {
           short zoneid = this->getEmptyMinionZone(card->getOwner());

           if (zoneid!=-1)
           {
                this->summonMinion(card, zoneid);
           }
        }
        else if (type=='1')
        {

        }

        this->getPlayer(this->getTurnPlayer())->changeMana(-cost);
    }

}
