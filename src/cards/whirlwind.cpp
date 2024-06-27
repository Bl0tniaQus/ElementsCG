#include "whirlwind.h"
#include "../duel.h"
#include "../card.h"
#include "../zone.h"
#include <iostream>
bool Whirlwind::onSpell(Duel* duel, Card* card)
{
    this->getOnSpellTargetList(duel, card);
    Card** targets = this->getTargetList()->getTargetList();
    short nt = this->getTargetList()->getTargetsNumber();
    if (nt>0)
    {
        int target;
        for (int i=0;i<nt;i++)
        {
            std::cout<<i<<" - "<<targets[i]->getName()<<std::endl;
        }
        std::cout<<"Target: ";
        std::cin>>target;
        Card* targetCard = targets[target];
        duel->toHand(targetCard);
        this->setTargetList(nullptr,0);
        return true;
    }
    return false;
}
void Whirlwind::getOnSpellTargetList(Duel* duel, Card* card)
{
    this->minionsOnField(duel, card);
}

