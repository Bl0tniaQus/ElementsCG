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
    this->minionsOnYourFieldWithExactName(duel,card,"Topaz Amber Fossil");
}
void TopazMantis::getSecondMaterialList(Duel* duel, Card* card)
{
    this->minionsOnYourFieldWithSameElement(duel,card,"Earth");
}
void TopazMantis::onSummon(Duel* duel, Card* card)
{
    card->setAttacks(2);
}
void TopazMantis::onTurnStart(Duel * duel, Card * card)
{
    card->setAttacks(2);
}
void TopazMantis::onDestroy(Duel* duel, Card* card)
{

        this->minionsOnYourFieldWithSameElement(duel,card,"Earth");
        short nt = this->getTargetList()->getTargetsNumber();
        Card** cards = this->getTargetList()->getTargetList();
        short deckSize = card->getOwner()->getDeckSize();
        if (deckSize>0 || nt>0) {this->secondEffectLog(duel, card);}
        for (short i=0;i<nt;i++)
        {
            duel->changeStats(cards[i],2,2);
        }
        if (card->getOwner()->getDeckSize()>0)
        {
            duel->drawCard(card->getOwner());
        }
}




