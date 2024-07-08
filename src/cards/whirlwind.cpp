#include "whirlwind.h"
#include "../engine/duel.h"
#include "../engine/card.h"
#include "../engine/zone.h"
#include "../engine/bot.h"
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

