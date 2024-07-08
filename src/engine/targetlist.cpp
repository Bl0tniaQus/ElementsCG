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
void TargetList::setTargetList(Card** targets, short n)
{

    delete [] this->targetList;
    this->targetList = new Card* [n];
    if (n==1) {this->targetList[0] = targets[0];}
    else{
    for (int i=0;i<n;i++)
    {
        this->targetList[i] = targets[i];
    }
    }
    this->n_targets = n;
}
TargetList::~TargetList()
{
    delete [] targetList;
}

