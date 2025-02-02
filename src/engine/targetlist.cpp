#include "targetlist.h"
#include "duel.h"
#include "zone.h"
TargetList::TargetList()
{
    this->targetList = std::vector<Card*>(0);
}
TargetList::TargetList(std::vector<Card*>& targetList)
{
    this->targetList = targetList;
}
void TargetList::setTargetList(std::vector<Card*>& targets)
{
    if (targets.size() == 0) {this->targetList = {}; return;}
    this->targetList = std::vector<Card*>(targets);
}
TargetList::~TargetList()
{

}
void TargetList::clearTargetList()
{
    this->targetList = std::vector<Card*>(0);
}
bool TargetList::cardNotNull(Card* card)
{
    return card!=nullptr;
}
void TargetList::addToTargetList(Card* card)
{
    if (this->cardNotNull(card)) this->targetList.push_back(card);
}
std::vector<Card *> TargetList::listSum(std::vector<Card *>& a, std::vector<Card *>& b)
{
    std::vector<Card* >c;
    c.insert(b.end(), a.begin(), a.end());
    return c;
}
std::vector<Card *> TargetList::listDifference(std::vector<Card *>& a, std::vector<Card *>& b)
{
    std::vector<short> duplicates;
    for (short i = 0; i<b.size(); i++)
    {
        for (short j = 0; j<a.size(); j++)
        {
            if (a[j] == b[i])
            {
                duplicates.push_back(i);
            }
        }
    }
    std::sort(duplicates.begin(), duplicates.end());
    for (short i = duplicates.size()-1; i>=0; i--)
    {
        a.erase(a.begin()+duplicates[i]);
    }
    return a;
}
std::vector<Card *> TargetList::listIntersect(std::vector<Card *>& a, std::vector<Card *>& b)
{
    std::vector<Card*> duplicates;
    for (short i = 0; i<b.size(); i++)
    {
        for (short j = 0; j<a.size(); j++)
        {
            if (a[j] == b[i])
            {
                duplicates.push_back(a[j]);
            }
        }
    }
    return duplicates;
}
bool TargetList::isPresent(Card* card)
{
    return true;
}
std::vector<Card *> TargetList::filterPlayer(std::vector<Card *>& l, Player* player)
{
    std::vector<Card*> newl;
    for (Card* card : l)
    {
        if (card->getOwner()==player)
        {
            newl.push_back(card);
        }
    }
    return newl;
}
std::vector<Card *> TargetList::filterOneElement(std::vector<Card *>& l, const std::string& element)
{
    std::vector<Card*> newl;
    for (Card* card : l)
    {
        if (card->getElement()==element)
        {
            newl.push_back(card);
        }
    }
    return newl;
}
std::vector<Card *> TargetList::filterTwoElements(std::vector<Card *>& l, const std::string& element1, const std::string& element2)
{
    std::vector<Card*> newl;
    for (Card* card : l)
    {
        if (card->getElement()==element1 || card->getElement() == element2)
        {
            newl.push_back(card);
        }
    }
    return newl;
}
std::vector<Card *> TargetList::filterOutOneElement(std::vector<Card *>& l, const std::string& element)
{
    std::vector<Card*> newl;
    for (Card* card : l)
    {
        if (card->getElement()!=element)
        {
            newl.push_back(card);
        }
    }
    return newl;
}
std::vector<Card *> TargetList::filterLevelRange(std::vector<Card *>& l, short a, short b)
{
    std::vector<Card*> newl;
    for (Card* card : l)
    {
        if (card->getLevel()>=a && card->getLevel()<=b)
        {
            newl.push_back(card);
        }
    }
    return newl;
}
std::vector<Card *> TargetList::filterCardName(std::vector<Card *>& l, const std::string& name)
{
    std::vector<Card*> newl;
    for (Card* card : l)
    {
        if (card->getName() == name)
        {
            newl.push_back(card);
        }
    }
    return newl;
}
std::vector<Card *> TargetList::filterOutCardName(std::vector<Card *>& l, const std::string& name)
{
    std::vector<Card*> newl;
    for (Card* card : l)
    {
        if (card->getName() == name)
        {
            newl.push_back(card);
        }
    }
    return newl;
}
std::vector<Card *> TargetList::filterNamePart(std::vector<Card *>& l, const std::string& namepart)
{
    std::vector<Card*> newl;
    for (Card* card : l)
    {
        if (card->getName().find(namepart)!=std::string::npos)
        {
            newl.push_back(card);
        }
    }
    return newl;
}
std::vector<Card*> TargetList::filterOutNamePart(std::vector<Card *>& l, const std::string& namepart)
{
    std::vector<Card*> newl;
    for (Card* card : l)
    {
        if (card->getName().find(namepart)==std::string::npos)
        {
            newl.push_back(card);
        }
    }
    return newl;
}
std::vector<Card*> TargetList::filterOutCopy(std::vector<Card *>& l, Card* c)
{
    std::vector<Card*> newl;
    for (Card* card : l)
    {
        if (card != c)
        {
            newl.push_back(card);
        }
    }
    return newl;
}
std::vector<Card*> TargetList::filterCardType(std::vector<Card *>& l, short type)
{
    std::vector<Card*> newl;
    for (Card* card : l)
    {
        if (card->getCardType() == type)
        {
            newl.push_back(card);
        }
    }
    return newl;
}
std::vector<Card*> TargetList::filterOutCardType(std::vector<Card *>& l, short type)
{
    std::vector<Card*> newl;
    for (Card* card : l)
    {
        if (card->getCardType() != type)
        {
            newl.push_back(card);
        }
    }
    return newl;
}
std::vector<Card *> TargetList::allMinionsOnField(Duel* duel)
{
    std::vector<Card*> targets = std::vector<Card*>(0);
    Zone* zone;
    Player* player;
    player = duel->getPlayer(duel->getTurnPlayer())->getOpponent();
    for (int i=0;i<5;i++)
        {
            zone = &player->getMinionField()[i];
            Card *cardd = zone->getCard();
            if (cardd!=nullptr){targets.push_back(cardd);}}
        player = duel->getPlayer(duel->getTurnPlayer());
        for (int i=0;i<5;i++)
        {
            zone = &player->getMinionField()[i];
            Card *cardd = zone->getCard();
            if (cardd!=nullptr){targets.push_back(cardd);}
        }
        return targets;
}
std::vector<Card *> TargetList::cardsInDeck(Player* player)
{
    std::vector<Card*> deck(*player->getDeck());
    return deck;
}
std::vector<Card *> TargetList::cardsInHand(Player* player)
{
    std::vector<Card*> hand(*player->getHand());
    return hand;
}
std::vector<Card *> TargetList::cardsInGraveyard(Player* player)
{
    std::vector<Card*> gy(*player->getGraveyard());
    return gy;
}
std::vector<Card *> TargetList::nTopCards(std::vector<Card *>& l, short n)
{
    std::vector<Card*> targets(0);
    for (int i = l.size()-(n+1); i<l.size(); i++)
    {
        targets.push_back(l[i]);
    }
    return targets;
}



