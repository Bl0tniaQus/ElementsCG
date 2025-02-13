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
    void targetListFromVector(std::vector<Card*>& v);
    static std::vector<Card*> allMinionsOnField(Duel* duel);
    static std::vector<Card*> cardsInGraveyard(Player* player);
    static std::vector<Card*> cardsInHand(Player* player);
    static std::vector<Card*> cardsInDeck(Player* player);
    static std::vector<Card*> filterOneElement(std::vector<Card*>& l, const std::string& element);
    static std::vector<Card*> filterTwoElements(std::vector<Card*>& l, const std::string& element1, const std::string& element2);
    static std::vector<Card*> filterOutOneElement(std::vector<Card*>& l, const std::string& element);
    static std::vector<Card*> filterPlayer(std::vector<Card*>& l, Player* player);
    static std::vector<Card*> filterCardName(std::vector<Card*>& l, const std::string& name);
    static std::vector<Card*> filterOutCardName(std::vector<Card*>& l, const std::string& name);
    static std::vector<Card*> filterNamePart(std::vector<Card*>& l, const std::string& namepart);
    static std::vector<Card*> filterOutNamePart(std::vector<Card*>& l, const std::string& namepart);
    static std::vector<Card*> filterOutCopy(std::vector<Card*>& l, Card* c);
    static std::vector<Card*> filterLevelRange(std::vector<Card*>& l, short a, short b);
    static std::vector<Card*> filterCardType(std::vector<Card*>& l, short type);
    static std::vector<Card*> filterOutCardType(std::vector<Card*>& l, short type);
    static std::vector<Card*> filterHavingElementInMaterialList(std::vector<Card*>& l, const std::string& element);
    static std::vector<Card*> nTopCards(std::vector<Card*>& l, short n);
    static std::vector<Card*> filterUniqueNames(std::vector<Card*>& l);
    static std::vector<Card*> listSum(std::vector<Card*>& a, std::vector<Card*>& b);
    static std::vector<Card*> listIntersect(std::vector<Card*>& a, std::vector<Card*>& b);
    static std::vector<Card*> listDifference(std::vector<Card*>& a, std::vector<Card*>& b);
};

#endif // TARGETLIST_H
