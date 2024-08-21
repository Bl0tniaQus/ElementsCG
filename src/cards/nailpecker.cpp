#include "nailpecker.h"
#include "../engine/duel.h"
#include "../engine/card.h"
void Nailpecker::onSummon(Duel* duel, Card* card)
{
    this->allMinionsOnField(duel,card);
    this->cardsWithSameElementInTargetList("Earth");
    short n = this->getTargetList()->getTargetsNumber();
    if (n>0)
    {
        this->effectLog(duel, card);
        duel->changeStats(card,1,0);
        duel->changeLevel(card,1);
    }


}
