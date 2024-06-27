#include "cardbase.h"
#include <cstring>
#include "../targetlist.h"
#include "../zone.h"
#include "../duel.h"
#include "../card.h"
CardBase::CardBase(short cid, short c, short ct, short l, short a, short d, const char* el, const char* n)
{
    this->cardId = cid;
    this->cost = c;
    this->cardType = ct;
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
    this->targetList->setTargetList(tl);
    this->targetList->setTargetNumber(n);
}
void CardBase::minionsOnField(Duel* duel, Card* card)
{
    short n_targets=0;
    Card** targets = new Card* [n_targets];
    for (int i=0;i<5;i++)
        {
            Card *card = duel->getPlayer(duel->getTurnPlayer())->getOpponent()->getMinionField()[i].getCard();

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
        for (int i=0;i<5;i++)
        {
            Card *card = duel->getPlayer(duel->getTurnPlayer())->getMinionField()[i].getCard();
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
                newtargets[n_targets-1] = card;
                delete [] targets;
                targets = newtargets;
            } else {newtargets[0]=card; targets = newtargets;}
            }

    }
    this->setTargetList(targets,n_targets);
}
