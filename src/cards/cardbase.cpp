#include "cardbase.h"
#include <cstring>
#include "../targetlist.h"
#include "../zone.h"
#include "../duel.h"
#include "../card.h"
#include "../bot.h"
#include <iostream>
CardBase::CardBase(short cid, short c, short ct, short l, short a, short d, const char* el, const char* n)
{
    this->cardId = cid;
    this->cost = c;
    this->cardType = ct;
    this->level = l;
    this->attack = a;
    this->defence = d;
    this->targetList = new TargetList;
    this->element = new char[strlen(el)+1];
    strcpy(this->element, el);
    this->name = new char[strlen(n)+1];
    strcpy(this->name, n);
}
void CardBase::setTargetList(Card** tl, short n)
{
    this->targetList->setTargetList(tl, n);
}
void CardBase::onTurnStart(Duel* duel, Card* card)
{
    if (card->getCardType()!=0&&card->getPlace()==2)
    {
        card->setAttacks(1);
    }
}
short CardBase::singleChoice(Duel* duel, Card* card)
{
    Card** targets = this->getTargetList()->getTargetList();
    short nt = this->getTargetList()->getTargetsNumber();
    Player* owner = card->getOwner();
    Bot* bot = owner->getBot();
    if (bot!=nullptr&&!bot->isTestingTargets())
    {
        if (bot->getTestedNumber()==-1)
        {
            bot->setChoicesNumber(nt);
            bot->setTestedNumber(0);
            bot->setTargetTesting(true);

        }

    }
    short target;
    if (nt>0)
    {
        if (owner->getBot()==nullptr)
        {
            std::cout<<"0 - cancel"<<std::endl;
            for (int i=0;i<nt;i++)
            {
                std::cout<<i+1<<" - "<<targets[i]->getName()<<std::endl;
            }
            std::cout<<"Target: ";
            std::cin>>target;
            if (target>=0 && target<=nt) {return target-1;}
            else {return -1;}
        }
        else
        {
            if (bot->isTesting())
            {
                return bot->getTestedNumber();
            }
            else {return bot->getBestTarget();}
        }
    }
    return -1;
}
void CardBase::minionsOnField(Duel* duel, Card* card)
{
    short n_targets=0;
    Card** targets = new Card* [n_targets];
    Zone* zone;
    Player* player;
    player = duel->getPlayer(duel->getTurnPlayer())->getOpponent();
    for (int i=0;i<5;i++)
        {
            zone = &player->getMinionField()[i];
            Card *cardd = zone->getCard();

            if (cardd!=nullptr)
            {

            n_targets++;
            Card **newtargets = new Card* [n_targets];
            if (n_targets>1) {
                for (int j=0;j<n_targets;j++)
                {

                    newtargets[j] = targets[j];

                }
                newtargets[n_targets-1] = cardd;
                delete [] targets;
                targets = newtargets;
            } else {newtargets[0]=cardd; targets = newtargets;}
            }
        }
        player = duel->getPlayer(duel->getTurnPlayer());
        for (int i=0;i<5;i++)
        {
            zone = &player->getMinionField()[i];
            Card *cardd = zone->getCard();
            if (cardd!=nullptr)
            {
            n_targets++;
            Card **newtargets = new Card* [n_targets];
            if (n_targets>1) {
                for (int j=0;j<n_targets;j++)
                {

                    newtargets[j] = targets[j];

                }
                newtargets[n_targets-1] = cardd;
                delete [] targets;
                targets = newtargets;
            } else {newtargets[0]=cardd; targets = newtargets;}
            }
        }
        this->setTargetList(targets,n_targets);
}

void CardBase::cardsInHandWithTheSameName(Duel* duel, Card* card)
{
    short handSize = card->getOwner()->getHandSize();
    short n_targets = 0;
    Card** targets = new Card* [n_targets];
    for (int i=0;i<handSize;i++)
        {
            Card *target = card->getOwner()->getHand()[i];
            if ((target!=nullptr)&&(target->getCardId() == card->getCardId())&&(card!=target))
            {
            n_targets++;
            Card **newtargets = new Card* [n_targets];
            if (n_targets>1) {
                for (int j=0;j<n_targets;j++)
                {
                    newtargets[j] = targets[j];

                }
                newtargets[n_targets-1] = target;
                delete [] targets;
                targets = newtargets;
            } else {newtargets[0]=target; targets = newtargets;}
            }

    }
    this->setTargetList(targets,n_targets);
}
bool CardBase::checkSummoningConditions2(Duel* duel, Card* card)
{
        bool result = true;
        this->setTargetList(nullptr,0);
        this->getFirstMaterialList(duel, card);
        short n_targets1 = this->getTargetList()->getTargetsNumber();
        Card** temp_targets = this->getTargetList()->getTargetList();
        Card** targets1 = new Card* [n_targets1];
        for (int i=0;i<n_targets1;i++)
        {
            targets1[i] = temp_targets[i];
        }
        this->setTargetList(nullptr,0);
        this->getSecondMaterialList(duel, card);
        short n_targets2 = this->getTargetList()->getTargetsNumber();
        temp_targets = this->getTargetList()->getTargetList();
        Card** targets2 = new Card* [n_targets2];
        for (int i=0;i<n_targets2;i++)
        {
            targets2[i] = temp_targets[i];
        } delete []temp_targets;

        if ((n_targets1==0)||(n_targets2==0)) {result = false;}
        else if ((n_targets1==1)&&(n_targets2==1))
        {
            if (targets1[0]==targets2[0]) {result = false;}
        }
        else if ((n_targets1==1)&&(n_targets2>1))
        {
            for (int i=0;i<n_targets2;i++)
            {
                if (targets2[i]==targets1[0]) {result = false;}
            }
        }
        else if ((n_targets2==1)&&(n_targets1>1))
        {
            for (int i=0;i<n_targets2;i++)
            {
                if (targets2[i]==targets1[0]) {result = false;}
            }
        }
    delete[] targets1;
    delete[] targets2;
    this->setTargetList(nullptr,0);
    return result;
}
bool CardBase::specialSummon2(Duel* duel, Card* card)
{
    if (checkSummoningConditions2(duel,card))
    {
        this->setTargetList(nullptr,0);
        this->getFirstMaterialList(duel, card);
        short n_targets1 = this->getTargetList()->getTargetsNumber();
        Card** targets1 = this->getTargetList()->getTargetList();
        int target;
        for (int i=0;i<n_targets1;i++)
        {
            std::cout<<i<<" - "<<targets1[i]->getName()<<std::endl;
        }
        std::cout<<"First minion: ";
        std::cin>>target;
        Card* targetCard = targets1[target];
        Card* targetCard2;
        this->setTargetList(nullptr,0);
        this->getSecondMaterialList(duel, card);
        short n_targets2 = this->getTargetList()->getTargetsNumber();
        Card** targets2 = this->getTargetList()->getTargetList();
        Card** new_targets2;
        short duplicate=0;
        for (int i=0;i<n_targets2;i++)
        {
            if (targets2[i]==targetCard)
            {
                duplicate=1;
                new_targets2 = new Card* [n_targets2-1];
                short bias=0;
                for (int j=0;j<n_targets2;j++)
                {
                   if (targets2[j]==targetCard) {bias=1; continue;}
                   new_targets2[j-bias]=targets2[j];
                }
            }
        }
        if (duplicate==1)
        {
            for (int i=0;i<n_targets2-1;i++)
            {
                std::cout<<i<<" - "<<new_targets2[i]->getName()<<std::endl;
            }
            std::cout<<"Second minion: ";
            std::cin>>target;
            targetCard2 = new_targets2[target];
        }
        else
        {
            for (int i=0;i<n_targets2;i++)
            {
                std::cout<<i<<" - "<<targets2[i]->getName()<<std::endl;
            }
            std::cout<<"Second minion: ";
            std::cin>>target;
            targetCard2 = targets2[target];
        }
        duel->removeFromField(targetCard);
        duel->removeFromField(targetCard2);
        duel->toGraveyard(targetCard);
        duel->toGraveyard(targetCard2);
        return true;
    }
    return false;
}
bool CardBase::checkSummoningConditions3(Duel* duel, Card* card)
{
    return true;
}
void CardBase::getMinionsWithSameElement(Duel* duel, Card* card, const char* element)
{
    this->setTargetList(nullptr,0);
    short n_targets=0;
    Card** targets = new Card* [n_targets];
    Player* owner = card->getOriginalOwner();
        for (int i=0;i<5;i++)
        {
            Card* card = owner->getMinionField()[i].getCard();
            if (card!=nullptr)
            {
                if (strcmp(element, card->getElement())==0)
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

    this->setTargetList(targets,n_targets);
}
void CardBase::getMinionsWithSameElementAndMinimumLevel(Duel* duel, Card* card, const char* element, short lvl)
{
    {
    this->setTargetList(nullptr,0);
    short n_targets=0;
    Card** targets = new Card* [n_targets];
    Player* owner = card->getOriginalOwner();
        for (int i=0;i<5;i++)
        {
            Card* card = owner->getMinionField()[i].getCard();
            if (card!=nullptr)
            {
                if (strcmp(element, card->getElement())==0&&card->getLevel()>=lvl)
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

    this->setTargetList(targets,n_targets);
}
}
