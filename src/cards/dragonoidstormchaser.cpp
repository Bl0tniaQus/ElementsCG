#include "dragonoidstormchaser.h"
#include "../engine/card.h"
#include "../engine/duel.h"
#include "../engine/zone.h"
bool DragonoidStormChaser::specialSummon(Duel* duel, Card* card)
{
    return this->specialSummon2(duel, card);
}
void DragonoidStormChaser::getFirstMaterialList(Duel* duel, Card* card)
{
    this->getMinionsWithSameElementAndMinimumLevel(duel,card,"Air",5);
}
void DragonoidStormChaser::getSecondMaterialList(Duel* duel, Card* card)
{
    this->getMinionsWithSameElement(duel,card,"Air");
}
void DragonoidStormChaser::onSummon(Duel* duel, Card* card)
{

}



