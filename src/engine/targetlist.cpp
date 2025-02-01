#include "targetlist.h"
TargetList::TargetList()
{
    this->targetList = new std::vector<Card*>;
}
TargetList::TargetList(std::vector<Card*>* targetList)
{
delete this->targetList;
this->targetList = targetList;
}
void TargetList::setTargetList(std::vector<Card*>* targets)
{
    if (targets==nullptr) {return;}
    delete this->targetList;
    this->targetList = new std::vector<Card*>;
    for (int i = 0; i<targets->size(); i++)
    {
        this->targetList->push_back(targets->at(i));
    }
}
TargetList::~TargetList()
{
    delete targetList;
}

