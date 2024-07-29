#include "topazmantis.h"
#include "../engine/card.h"
#include "../engine/duel.h"
#include "../engine/zone.h"
bool TopazMantis::specialSummon(Duel* duel, Card* card)
{
    return this->specialSummon2(duel, card);
}
void TopazMantis::getFirstMaterialList(Duel* duel, Card* card)
{
    this->getMinionsWithSameElement(duel,card,"Earth");
}
void TopazMantis::getSecondMaterialList(Duel* duel, Card* card)
{
    this->getMinionsWithSameElement(duel,card,"Earth");
}
void TopazMantis::onSummon(Duel* duel, Card* card)
{
    this->firstEffectLog(duel, card);
    duel->appendLog(duel->barrierChangeLog(card, 1), duel->getLastSource());
    card->setBarrier(1);
}
void TopazMantis::onTurnStart(Duel * duel, Card * card)
{
    card->setAttacks(1);
    if (card->getBarrier()==0) {
        this->secondEffectLog(duel, card);
        duel->appendLog(duel->barrierChangeLog(card, 1), duel->getLastSource());
        card->setBarrier(1);

    }
}


