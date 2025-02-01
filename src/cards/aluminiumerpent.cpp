#include "aluminiumserpent.h"
#include "../engine/duel.h"
#include "../engine/card.h"
void AluminiumSerpent::onSummon(Duel* duel, Card* card)
{
    this->minionsInYourGraveyardWithSameElementAndMaximumLevel(duel,card,"Earth",2);
    short n = this->getTargetList()->getTargetsNumber();
    std::vector<Card*>* tl = this->getTargetList()->getTargetList();
    if (n>0)
    {
    this->effectLog(duel, card);
    Card* target = tl->at(0);
    duel->toHand(target);
    duel->removeFromGraveyard(target);
    }
}

