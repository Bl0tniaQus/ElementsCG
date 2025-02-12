#include "wind-upairplane.h"
#include "../engine/card.h"
#include "../engine/duel.h"
#include "../engine/zone.h"
bool WindUpAirplane::specialSummon(Duel* duel, Card* card)
{
    return this->specialSummon2(duel, card);
}
void WindUpAirplane::getFirstMaterialList(Duel* duel, Card* card)
{
    this->minionsOnYourFieldWithSameElement(duel,card->getOwner(),"Air");
}
void WindUpAirplane::getSecondMaterialList(Duel* duel, Card* card)
{
    this->minionsOnYourFieldWithOneOfTwoElements(duel,card->getOwner(),"Air","Earth");
}
void WindUpAirplane::onSummon(Duel* duel, Card* card)
{
    if (!card->getIsNegated())
    {
        int val = this->getNumericValues()->at(0);
        val = val + 2;
        this->getNumericValues()->at(0) = val;
        this->effectLog(duel, card);
        duel->changeStats(card,2,0);
    }
}
void WindUpAirplane::onTurnStart(Duel* duel, Card* card)
{
    card->setAttacks(1);
    int val = this->getNumericValues()->at(0);
    if (!card->getIsNegated() && val > 0)
    {
        this->getNumericValues()->at(0) = val - 1;
        this->effectLog(duel, card);
        duel->changeStats(card,-1,0);
    }
}


