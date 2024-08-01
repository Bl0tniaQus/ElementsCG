#include "ambertreant.h"
#include "../engine/card.h"
#include "../engine/duel.h"
#include "../engine/zone.h"
bool AmberTreant::specialSummon(Duel* duel, Card* card)
{
    return this->specialSummon2(duel, card);
}
void AmberTreant::getFirstMaterialList(Duel* duel, Card* card)
{
    //this->getMinionsWithSameElement(duel,card,"Earth");
}
void AmberTreant::getSecondMaterialList(Duel* duel, Card* card)
{
   // this->getMinionsWithSameElement(duel,card,"Earth");
}
void AmberTreant::onSummon(Duel* duel, Card* card)
{
    this->firstEffectLog(duel, card);
    duel->appendLog(duel->barrierChangeLog(card, 1), duel->getLastSource());
    card->setBarrier(1);
}
void AmberTreant::onTurnStart(Duel * duel, Card * card)
{
    card->setAttacks(1);
    if (card->getBarrier()==0) {
        this->secondEffectLog(duel, card);
        duel->appendLog(duel->barrierChangeLog(card, 1), duel->getLastSource());
        card->setBarrier(1);

    }
}


