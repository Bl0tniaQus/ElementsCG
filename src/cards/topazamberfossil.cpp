#include "topazamberfossil.h"
#include "../engine/duel.h"
#include "../engine/card.h"
void TopazAmberFossil::onSummon(Duel* duel, Card* card)
{
    this->getOnSummonTargetList(duel, card);
    short n = this->getTargetList()->getTargetsNumber();
    Card** tl = this->getTargetList()->getTargetList();
    if (n>0)
    {
    this->effectLog(duel, card);
    Card* target = tl[0];
    duel->toHand(target);
    duel->removeFromGraveyard(target);
    }
}
void TopazAmberFossil::getOnSummonTargetList(Duel* duel, Card* card)
{
    this->specialMinionsInYourGraveyardWithSameElement(duel,card,"Earth");
}

