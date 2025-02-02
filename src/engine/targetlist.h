#ifndef TARGETLIST_H
#define TARGETLIST_H
#include <vector>
#include <string>
class Card;
class Duel;
class Player;
class TargetList
{
private:
    std::vector<Card*> targetList;
public:
    TargetList();
    ~TargetList();
    TargetList(std::vector<Card*>& targetList);
    std::vector<Card*>* getTargetList() {return &this->targetList;}
    short getTargetsNumber() {return this->targetList.size();}
    void setTargetList(std::vector<Card*>& targets);
    bool isPresent(Card* card);
    bool cardNotNull(Card* card);
    void clearTargetList();
    void addToTargetList(Card* card);
    std::vector<Card*> allMinionsOnField(Duel* duel);
    std::vector<Card*> cardsInGraveyard(Player* player);
    std::vector<Card*> cardsInHand(Player* player);
    std::vector<Card*> cardsInDeck(Player* player);
    std::vector<Card*> filterOneElement(std::vector<Card*>& l, const std::string& element);
    std::vector<Card*> filterTwoElements(std::vector<Card*>& l, const std::string& element1, const std::string& element2);
    std::vector<Card*> filterOutOneElement(std::vector<Card*>& l, const std::string& element);
    std::vector<Card*> filterPlayer(std::vector<Card*>& l, Player* player);
    std::vector<Card*> filterCardName(std::vector<Card*>& l, const std::string& name);
    std::vector<Card*> filterOutCardName(std::vector<Card*>& l, const std::string& name);
    std::vector<Card*> filterNamePart(std::vector<Card*>& l, const std::string& namepart);
    std::vector<Card*> filterOutNamePart(std::vector<Card*>& l, const std::string& namepart);
    std::vector<Card*> filterOutCopy(std::vector<Card*>& l, Card* c);
    std::vector<Card*> filterLevelRange(std::vector<Card*>& l, short a, short b);
    std::vector<Card*> filterCardType(std::vector<Card*>& l, short type);
    std::vector<Card*> filterOutCardType(std::vector<Card*>& l, short type);
    std::vector<Card*> nTopCards(std::vector<Card*>& l, short n);
    std::vector<Card*> listSum(std::vector<Card*>& a, std::vector<Card*>& b);
    std::vector<Card*> listIntersect(std::vector<Card*>& a, std::vector<Card*>& b);
    std::vector<Card*> listDifference(std::vector<Card*>& a, std::vector<Card*>& b);
};

#endif // TARGETLIST_H
