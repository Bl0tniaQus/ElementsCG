#include "wind-upbiplane.h"
#include "../engine/card.h"
#include "../engine/duel.h"
#include "../engine/zone.h"
bool WindUpBiplane::specialSummon(Duel* duel, Card* card)
{
    return this->specialSummon2(duel, card);
}
void WindUpBiplane::getFirstMaterialList(Duel* duel, Card* card)
{
    this->minionsOnYourFieldWithSameElementAndMinimumLevel(duel,card->getOwner(),"Air", 3);
}
void WindUpBiplane::getSecondMaterialList(Duel* duel, Card* card)
{
    this->minionsOnYourFieldWithOneOfTwoElements(duel,card->getOwner(),"Air","Earth");
}
void WindUpBiplane::onSummon(Duel* duel, Card* card)
{
    if (!card->getIsNegated())
    {
        int val = this->getNumericValues()->at(0);
        val = val + 2;
        short barrier = card->getBarrier();
        this->getNumericValues()->at(0) = val;
        this->effectLog(duel, card);
        duel->changeStats(card,2,2);
        duel->changeBarrier(card,barrier+1);
    }
}
void WindUpBiplane::onTurnStart(Duel* duel, Card* card)
{
    card->setAttacks(1);
    int val = this->getNumericValues()->at(0);
    if (!card->getIsNegated() && val > 0)
    {
        this->getNumericValues()->at(0) = val - 1;
        this->effectLog(duel, card);
        duel->changeStats(card,-1,-1);
    }
}


