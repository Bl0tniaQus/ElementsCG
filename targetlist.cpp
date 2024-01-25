#include "targetlist.h"
TargetList::TargetList()
{
    this->targetList = new Card* [0];
    this->n_targets = 0;
}
TargetList::TargetList(Card** targetList, short n_targets)
{
delete [] this->targetList;
this->targetList = targetList;
this->n_targets=n_targets;
}
void TargetList::setTargetList(Card** targets)
{
    delete [] this->targetList;
    this->targetList = targets;
}
