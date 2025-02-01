#ifndef TARGETLIST_H
#define TARGETLIST_H
#include <vector>
class Card;
class TargetList
{
private:
    std::vector<Card*>* targetList;
public:
    TargetList();
    ~TargetList();
    TargetList(std::vector<Card*>* targetList);
    std::vector<Card*>* getTargetList() {return this->targetList;}
    short getTargetsNumber() {return this->targetList->size();}
    void setTargetList(std::vector<Card*>* targets);
};

#endif // TARGETLIST_H
