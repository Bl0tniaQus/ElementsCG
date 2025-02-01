#include "sadnimbus.h"
#include "../engine/duel.h"
#include "../engine/card.h"
void SadNimbus::onSummon(Duel* duel, Card* card)
{
    short mana = card->getOwner()->getMana();
    if (mana>=12)
    {
        this->cardsInYourGraveyardWithExactName(duel,card,"Sad Nimbus");
        short n = this->getTargetList()->getTargetsNumber();
        if (n==0) {return;}
        else
        {
            short zoneid = duel->getEmptyMinionZone(card->getOwner());
            Card* targetCard = this->getTargetList()->getTargetList()->at(0);
            if (zoneid!=-1) {
                this->effectLog(duel, card);
                duel->summonFromGraveyard(targetCard, zoneid);
            }
        }
    }
}

