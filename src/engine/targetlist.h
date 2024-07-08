#ifndef TARGETLIST_H
#define TARGETLIST_H
class Card;
class TargetList
{
private:
    Card** targetList;
    short n_targets;
public:
    TargetList();
    ~TargetList();
    TargetList(Card** targetList, short n_targets);
    Card** getTargetList() {return this->targetList;}
    short getTargetsNumber() {return this->n_targets;}
    void setTargetList(Card** targets, short n);
    void setTargetNumber(short n_targets) {this->n_targets = n_targets;}
};

#endif // TARGETLIST_H
