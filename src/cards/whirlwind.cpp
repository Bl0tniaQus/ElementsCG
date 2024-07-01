#include "whirlwind.h"
#include "../duel.h"
#include "../card.h"
#include "../zone.h"
#include <iostream>
bool Whirlwind::onSpell(Duel* duel, Card* card)
{
    this->getOnSpellTargetList(duel, card);
    Card** targets = this->getTargetList()->getTargetList();
    short target = singleChoice(duel,card);
    if (target==-1) {return false;}
    else
    {
        Card* targetCard = targets[target];
        duel->toHand(targetCard);
        this->setTargetList(nullptr,0);
        return true;
    }
}
void Whirlwind::getOnSpellTargetList(Duel* duel, Card* card)
{
    this->minionsOnField(duel, card);
}

