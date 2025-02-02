#include "angrycumulonimbus.h"
#include "../engine/card.h"
#include "../engine/duel.h"
#include "../engine/zone.h"
bool AngryCumulonimbus::specialSummon(Duel* duel, Card* card)
{
    return this->specialSummon2(duel, card);
}
void AngryCumulonimbus::getFirstMaterialList(Duel* duel, Card* card)
{
    this->minionsOnYourFieldWithExactName(duel,card->getOwner(),"Happy Cumulus");
}
void AngryCumulonimbus::getSecondMaterialList(Duel* duel, Card* card)
{
    this->minionsOnYourFieldWithExactName(duel,card->getOwner(),"Sad Nimbus");
}
void AngryCumulonimbus::onSummon(Duel* duel, Card* card)
{
    short mana = card->getOwner()->getMana();
    short atk = mana / 4;
    this->effectLog(duel, card);
    duel->changeStats(card,atk,0);
}



