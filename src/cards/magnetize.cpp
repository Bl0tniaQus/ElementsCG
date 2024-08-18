#include "magnetize.h"
#include "../engine/duel.h"
#include "../engine/card.h"
#include "../engine/zone.h"
#include "../engine/bot.h"
bool Magnetize::onSpell(Duel* duel, Card* card)
{

    this->minionsOnYourFieldWithSameElement(duel,card,"Earth");
    Card** targets = this->getTargetList()->getTargetList();
    short nt = this->getTargetList()->getTargetsNumber();
    if (nt<2) {return false;}
    short target = singleChoice(duel,card);
    if (target==-1) {return false;}
    else
    {
        this->spellFromHandLog(duel,card);
        this->spellCost(card);
        Card* targetCard = targets[target];
        short atk = 0;
        if (!targetCard->getIsSpellImmune())
        {

            for (short i=0; i<nt;i++)
            {
                if (targets[i]!=targetCard)
                {
                    atk+=targets[i]->getAttack();
                    targets[i]->setAttacks(0);
                }
            }
            this->target = targetCard;
            this->atkChange = atk;
            duel->changeStats(targetCard,atk,0);
            duel->addTurnEndLingeringEffect(card);
        }
        return true;
    }
}
void Magnetize::onTurnEnd(Duel* duel, Card* card)
{
    if (this->target->getPlace()==2)
    {
        this->effectLog(duel, card);
        duel->changeStats(this->target, -this->atkChange, 0);
        this->atkChange = 0;
        this->target = nullptr;
    }
}


