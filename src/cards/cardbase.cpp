#include "cardbase.h"
#include <cstring>
#include "../engine/targetlist.h"
#include "../engine/zone.h"
#include "../engine/duel.h"
#include "../engine/card.h"
#include "../engine/bot.h"
#include <iostream>
#include <QDebug>
CardBase::CardBase(short cid, short c, short ct, short l, short a, short d, const char* el, const char* n, const char * i, const char* ctx)
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
    this->image = new char[strlen(i)+1];
    strcpy(this->image, i);
    this->cardText = new char[strlen(ctx)+1];
    strcpy(this->cardText,ctx);
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
    if (bot!=nullptr&&!bot->isTestingTargets()&&bot->isTesting())
    {
        if (bot->getTestedNumber()==-1)
        {
            bot->setChoicesNumber(nt);
            bot->setTargetTesting(true);
            return -1;
        }

    }
    if (nt>0)
    {
        if (owner->getBot()==nullptr)
        {
                return duel->makeSpellChoice(card);
        }
        else
        {
            if (bot->isTesting())
            {
                return bot->getTestedNumber();
            }
            else
            {
                return bot->getBestTarget();
            }
        }
    }
    return -1;
}
void CardBase::allMinionsOnField(Duel* duel, Card* card)
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
void CardBase::minionsOnYourFieldWithSameElement(Duel* duel, Card* card, const char* element)
{
    short n_targets=0;
    Card** targets = new Card* [n_targets];
    Zone* zone;
    Player* player;
        player = card->getOwner();
        for (int i=0;i<5;i++)
        {
            zone = &player->getMinionField()[i];
            Card *cardd = zone->getCard();
            if (cardd!=nullptr)
            {
                if (strcmp(element, cardd->getElement())==0)
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
void CardBase::cardsInHandWithCommonNamePart(Duel* duel, Card* card, const char* namePart)
{
    short handSize = card->getOwner()->getHandSize();
    short n_targets = 0;
    Card** targets = new Card* [n_targets];
    for (int i=0;i<handSize;i++)
        {
            Card *target = card->getOwner()->getHand()[i];
            if ((target!=nullptr)&&(strstr(target->getName(),namePart)!=nullptr)&&(card!=target))
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
void CardBase::cardsInDeckWithCommonNamePart(Duel* duel, Card* card, const char* namePart)
{
    short deckSize = card->getOwner()->getDeckSize();
    short n_targets = 0;
    Card** targets = new Card* [n_targets];
    for (int i=0;i<deckSize;i++)
        {
            Card *target = card->getOwner()->getDeck()[i];
            if ((target!=nullptr)&&(strstr(target->getName(),namePart)!=nullptr)&&(card!=target))
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
void CardBase::minionsOnYourFieldWithCommonNamePart(Duel* duel, Card* card, const char* namePart)
{
    short n_targets = 0;
    Card** targets = new Card* [n_targets];
    Player* player = card->getOwner();
    Zone* zone;
    for (int i=0;i<5;i++)
        {
            zone = &player->getMinionField()[i];
            Card *cardd = zone->getCard();
            if (cardd!=nullptr)
            {
                if (strstr(cardd->getName(),namePart)!=nullptr)
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
        }
    this->setTargetList(targets,n_targets);
}
bool CardBase::checkSummoningConditions2(Duel* duel, Card* card)
{
        bool result = true;
        this->getFirstMaterialList(duel, card);
        short n_targets1 = this->getTargetList()->getTargetsNumber();
        Card** temp_targets = this->getTargetList()->getTargetList();
        Card** targets1 = new Card* [n_targets1];
        for (int i=0;i<n_targets1;i++)
        {
            targets1[i] = temp_targets[i];
        }
        this->getSecondMaterialList(duel, card);
        short n_targets2 = this->getTargetList()->getTargetsNumber();
        temp_targets = this->getTargetList()->getTargetList();
        Card** targets2 = new Card* [n_targets2];
        for (int i=0;i<n_targets2;i++)
        {
            targets2[i] = temp_targets[i];
        }

        if ((n_targets1==0)||(n_targets2==0)) {result = false;}
        else if ((n_targets1==1)&&(n_targets2==1))
        {
            if (targets1[0]==targets2[0]) {result = false;}
        }
        else if ((n_targets1==1)&&(n_targets2==1))
        {
            for (int i=0;i<n_targets2;i++)
            {
                if (targets2[i]==targets1[0]) {result = false;}
            }
        }
        else if ((n_targets2==1)&&(n_targets1==1))
        {
            for (int i=0;i<n_targets2;i++)
            {
                if (targets2[i]==targets1[0]) {result = false;}
            }
        }
    delete[] targets1;
    delete[] targets2;
    return result;
}
bool CardBase::specialSummon2(Duel* duel, Card* card)
{
    if (checkSummoningConditions2(duel,card))
    {
        this->getFirstMaterialList(duel, card);
        Card** targets1 = this->getTargetList()->getTargetList();
        int target;
        target = duel->makeSpecialMinionMaterialChoice(card);
        if (target==-1) {return false;}
        Card* targetCard = targets1[target];
        Card* targetCard2;
        this->getSecondMaterialList(duel, card);
        short n_targets2 = this->getTargetList()->getTargetsNumber();
        Card** targets2 = this->getTargetList()->getTargetList();
        Card** new_targets2;
        short n_targets2New = n_targets2;
        bool duplicate = 0;
        for (int i=0;i<n_targets2;i++)
        {
            if (targets2[i]==targetCard) {duplicate = true;}
        }
        if (duplicate)
            {
                new_targets2 = new Card* [n_targets2-1];
                short bias=0;
                for (int j=0;j<n_targets2;j++)
                {
                   if (targets2[j]==targetCard) {bias=1; n_targets2New = n_targets2-1; continue;}
                   new_targets2[j-bias]=targets2[j];
                }
            }
            else
            {
                new_targets2 = new Card* [n_targets2];
                for (int j=0;j<n_targets2;j++)
                {
                   new_targets2[j]=targets2[j];
                }
            }
        card->getCardName()->setTargetList(new_targets2,n_targets2New);
        target = duel->makeSpecialMinionMaterialChoice(card);
        if (target==-1) {return false;}
        targetCard2 = new_targets2[target];
        this->release2Log(targetCard,targetCard2, duel);
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

void CardBase::minionsOnYourFieldWithSameElementAndMinimumLevel(Duel* duel, Card* card, const char* element, short lvl)
{
    short n_targets=0;
    Card** targets = new Card* [n_targets];
    Player* owner = card->getOriginalOwner();
        for (int i=0;i<5;i++)
        {
            Card* cardd = owner->getMinionField()[i].getCard();
            if (cardd!=nullptr)
            {
                if (strcmp(element, cardd->getElement())==0&&cardd->getLevel()>=lvl)
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
        }

    this->setTargetList(targets,n_targets);
}
void CardBase::minionsOnYourFieldWithSameElementAndMaximumLevel(Duel* duel, Card* card, const char* element, short lvl)
{
    short n_targets=0;
    Card** targets = new Card* [n_targets];
    Player* owner = card->getOriginalOwner();
        for (int i=0;i<5;i++)
        {
            Card* cardd = owner->getMinionField()[i].getCard();
            if (cardd!=nullptr)
            {
                if (strcmp(element, cardd->getElement())==0&&cardd->getLevel()<=lvl)
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
        }

    this->setTargetList(targets,n_targets);
}

void CardBase::minionsInYourGraveyardWithSameElementAndMaximumLevel(Duel* duel, Card* card, const char* element, short lvl)
{
    short n_targets=0;
    Card** targets = new Card* [n_targets];
    Card** graveyard = card->getOwner()->getGraveyard();
    short n_graveyard = card->getOwner()->getGraveyardSize();
        for (int i=0;i<n_graveyard;i++)
        {
            Card* cardd = graveyard[i];
            if (strcmp(element, cardd->getElement())==0&&cardd->getLevel()<=lvl&&cardd->getCardType()==1)
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
void CardBase::specialMinionsInYourGraveyardWithSameElement(Duel* duel, Card* card, const char* element)
{
    short n_targets=0;
    Card** targets = new Card* [n_targets];
    Card** graveyard = card->getOwner()->getGraveyard();
    short n_graveyard = card->getOwner()->getGraveyardSize();
        for (int i=0;i<n_graveyard;i++)
        {
            Card* cardd = graveyard[i];
            if (strcmp(element, cardd->getElement())==0&&cardd->getCardType()==2)
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
void CardBase::minionsOnYourFieldWithExactName(Duel* duel, Card* card, const char* name)
{
    short n_targets=0;
    Card** targets = new Card* [n_targets];
    Player* owner = card->getOriginalOwner();
    Zone* zone;
    Card* cardd;
        for (int i=0;i<5;i++)
        {
            zone = &owner->getMinionField()[i];
            cardd = zone->getCard();

            if (cardd!=nullptr)
            {
                if (strcmp(name, cardd->getName())==0)
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
        }

    this->setTargetList(targets,n_targets);
}
void CardBase::spellCost(Card* card)
{
    card->getOwner()->changeMana(-card->getCost());
}
void CardBase::effectLog(Duel* duel, Card* card)
{
    std::string cardName = this->getName();
    std::string str = "["+cardName+"]"+"'s effect activates";
    duel->appendLog(str,duel->getPlayerId(card->getOwner()));
}
void CardBase::firstEffectLog(Duel* duel, Card* card)
{
    std::string cardName = this->getName();
    std::string str = "["+cardName+"]"+"'s first effect activates";
    duel->appendLog(str,duel->getPlayerId(card->getOwner()));
}
void CardBase::secondEffectLog(Duel* duel, Card* card)
{
    std::string cardName = this->getName();
    std::string str = "["+cardName+"]"+"'s second effect activates";
    duel->appendLog(str,duel->getPlayerId(card->getOwner()));
}
void CardBase::thirdEffectLog(Duel* duel, Card* card)
{
    std::string cardName = this->getName();
    std::string str = "["+cardName+"]"+"'s third effect activates";
    duel->appendLog(str,duel->getPlayerId(card->getOwner()));
}
void CardBase::release2Log(Card* c1, Card* c2, Duel* duel)
{
    std::string playerName = std::string(c1->getOwner()->getName());
    std::string n1 = std::string(c1->getName());
    std::string n2 = std::string(c2->getName());
    std::string str = "[" + playerName + "] releases [" + n1 + "] and [" + n2 + "]";
    duel->appendLog(str,duel->getPlayerId(c1->getOwner()));
}
void CardBase::release3Log(Card* c1, Card* c2, Card* c3, Duel* duel)
{

}
void CardBase::spellFromHandLog(Duel* duel, Card* card)
{
    duel->appendLog(duel->cardFromHandLog(card),duel->getPlayerId(card->getOwner()));
}


