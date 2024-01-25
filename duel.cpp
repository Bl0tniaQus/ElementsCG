#include "duel.h"
#include "card.h"
#include <iostream>
Duel::Duel()
{
    players[0].setOpponent(&players[1]);
    players[1].setOpponent(&players[0]);
    players[0].setName('a');
    players[1].setName('b');
    this->turnPlayer = 0;
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
    }
    return -1;
}
short Duel::getEmptySpellZone(Player* player)
{
    Zone* zones = player->getSpellField();
    for (int i=0;i<5;i++)
    {
        if (zones[i].getUsed()==false) {return i;}
    }
    return -1;
}
void Duel::summonMinion(Card *minion, short zoneid)
{
    if ((minion->getCardType()>0)&&(minion->getPlace()!=2))
    {
        minion->setPlace(2);
        minion->getOwner()->getMinionField()[zoneid].bindCard(minion);
        minion->getOwner()->getMinionField()[zoneid].setUsed(true);

    }
}
void Duel::activateSpell(Card *spell, short zoneid)
{
    if ((spell->getCardType()==0)&&(spell->getPlace()==1))
    {
        this->onSpell(spell,zoneid);
    }
}
void Duel::toHand(Card* card)
{
    card->setPlace(1);
    card->getZone()->setUsed(false);
    card->getZone()->destroyCard();
    card->setZone(nullptr);
    short n_hand = card->getOriginalOwner()->getHandSize();
    Card** oldHand = card->getOriginalOwner()->getHand();
    Card** newHand = new Card*[n_hand+1];
    if (n_hand==1) {newHand[0] = card;}
    else{
    for (int i=0;i<n_hand;i++)
    {
        newHand[i] = oldHand[i];
    }
    }
    newHand[n_hand] = card;
    card->getOriginalOwner()->setHand(newHand, n_hand+1);
    card->getOriginalOwner()->setHandSize(n_hand+1);
}
void Duel::drawCard(char p)
{
    short n_deck = this->getPlayer(p)->getDeckSize();
    if (n_deck>0)
    {
        short n_hand = this->getPlayer(p)->getHandSize();
        Card** oldHand = this->getPlayer(p)->getHand();
        Card** newHand = new Card*[n_hand+1];
        Card** newDeck = new Card*[n_deck-1];
        Card** oldDeck = this->getPlayer(p)->getDeck();

        if (n_hand==0) {newHand[0] = oldDeck[n_deck-1];}
        else{
        for (int i=0;i<n_hand;i++)
        {
            newHand[i] = oldHand[i];
        }
        }
        oldDeck[n_deck-1]->setPlace(1);
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
    this->setTargetList(nullptr,0);
    short id = card->getCardId();
    //any monster on field
if (id==4)
{
this->generateTargetList(card);
    if (this->targetList.getTargetsNumber()>0) {return true;}
}
//monster with the same name in hand
else if (id==1)
{
    this->generateTargetList(card);
        if (this->targetList.getTargetsNumber()>0) {return true;}
}
return false;
}
void Duel::onSpell(Card* card, short zoneid)
{
short id = card->getCardId();
if (id==4) //Whirlwind
{
    bool usable = this->checkEffectRequirements(card);
    if (usable)
    {
        Card** targets = this->targetList.getTargetList();
        int target;
        for (int i=0;i<this->targetList.getTargetsNumber();i++)
        {
            std::cout<<i<<" - "<<targets[i]->getName()<<std::endl;
        }
        std::cout<<"Target: ";
        std::cin>>target;
        Card* targetCard = targets[target];
        this->toHand(targetCard);
    }
}
}
void Duel::onSummon(Card* card, short zoneid)
{
    short id = card->getCardId();
    //summon minion from hand
    if (id==1)
    {
        bool usable = this->checkEffectRequirements(card);
        if (usable)
        {
            Card** targets = this->targetList.getTargetList();
            Card* targetCard = targets[0];
            this->summonFromHand(targetCard, this->getEmptyMinionZone(card->getOwner()));
        }
    }

}
void Duel::setTargetList(Card** targets, short n_targets)
{
    this->targetList.setTargetList(targets);
    this->targetList.setTargetNumber(n_targets);

}

void Duel::generateTargetList(Card* effect)
{
    short n_targets=0;
    Card** targets = new Card* [n_targets];
    short effectId = effect->getCardId();
    //any monster on field
    if (effectId==4)
    {
        for (int i=0;i<5;i++)
        {
            Card *card = this->players[getTurnPlayer()].getOpponent()->getMinionField()[i].getCard();

            if ((card!=nullptr)&&(card!=effect))
            {
            n_targets++;
            Card **newtargets = new Card* [n_targets];
            if (n_targets>1) {
                for (int j=0;j<n_targets;j++)
                {

                    newtargets[j] = targets[j];

                }
                newtargets[n_targets-1] = card;
                delete [] targets;
                targets = newtargets;
            } else {newtargets[0]=card; targets = newtargets;}
            }
        }
        for (int i=0;i<5;i++)
        {
            Card *card = this->players[getTurnPlayer()].getMinionField()[i].getCard();
            if (card!=nullptr)
            {
            n_targets++;
            Card **newtargets = new Card* [n_targets];
            if (n_targets>1) {
                for (int j=0;j<n_targets;j++)
                {

                    newtargets[j] = targets[j];

                }
                newtargets[n_targets-1] = card;
                delete [] targets;
                targets = newtargets;
            } else {newtargets[0]=card; targets = newtargets;}
            }
        }
    }
    //Monster in hand with the same name
    else if (effectId==1)
    {

        for (int i=0;i<effect->getOwner()->getHandSize();i++)
        {
            Card *card = effect->getOwner()->getHand()[i];
            if ((card!=nullptr)&&(card->getCardId()==effectId)&&(card!=effect))
            {

            n_targets++;
            Card **newtargets = new Card* [n_targets];
            if (n_targets>1) {
                for (int j=0;j<n_targets;j++)
                {

                    newtargets[j] = targets[j];

                }
                newtargets[n_targets-1] = card;
                delete [] targets;
                targets = newtargets;
            } else {newtargets[0]=card; targets = newtargets;}
            }

    }}
    this->setTargetList(targets,n_targets);
}
void Duel::playFromHand(Card* card)
{
    char type = card->getCardType();
    short cost = card->getCost();
    short zoneid;

    if ((cost<=card->getOwner()->getMana())||(card->getPlace()==1))
    {
        if (type==1)
        {
            zoneid = this->getEmptyMinionZone(card->getOwner());

           if (zoneid!=-1)
           {

               this->summonMinion(card, zoneid);
           }
        }
        else if (type==0)
        {
            zoneid = this->getEmptyMinionZone(card->getOwner());
            this->activateSpell(card,zoneid);
        }

        short n_hand = card->getOriginalOwner()->getHandSize();
        Card** oldHand = card->getOriginalOwner()->getHand();
        Card** newHand = new Card*[n_hand-1];
        short bias = 0;
        for (int i=0;i<n_hand;i++)
        {
            if (oldHand[i]==card) {bias = 1; continue;}
            newHand[i-bias] = oldHand[i];
        }

        card->getOriginalOwner()->setHand(newHand, n_hand-1);//tu problem
        card->getOriginalOwner()->setHandSize(n_hand-1);
        if (type==1) {this->onSummon(card, zoneid);}
        card->getOwner()->changeMana(-cost);
    }

}
void Duel::summonFromHand(Card* minion, short zoneid)
{
    if ((minion->getCardType()==1)&&(minion->getPlace()==1))
    {

        minion->setPlace(2);
        minion->getOwner()->getMinionField()[zoneid].bindCard(minion);
        minion->getOwner()->getMinionField()[zoneid].setUsed(true);
        short n_hand = minion->getOriginalOwner()->getHandSize();
        Card** oldHand = minion->getOriginalOwner()->getHand();
        Card** newHand = new Card*[n_hand-1];
        short bias = 0;
        for (int i=0;i<n_hand;i++)
        {
            if (oldHand[i]==minion) {bias = 1; continue;}
            newHand[i-bias] = oldHand[i];
        }
        minion->getOriginalOwner()->setHand(newHand, n_hand-1);
        minion->getOriginalOwner()->setHandSize(n_hand-1);
        this->onSummon(minion,this->getEmptyMinionZone(minion->getOwner()));
    }
}
