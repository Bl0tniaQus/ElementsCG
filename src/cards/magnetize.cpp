#include "magnetize.h"
#include "../engine/duel.h"
#include "../engine/card.h"
#include "../engine/zone.h"
#include "../engine/bot.h"
bool Magnetize::onSpell(Duel* duel, Card* card)
{
    this->getCardTargets()->clear();
    this->getNumericValues()->clear();
    this->minionsOnYourFieldWithSameElement(duel,card->getOwner(),"Earth");
    std::vector<Card*>* targets = this->getTargetList()->getTargetList();
    short nt = this->getTargetList()->getTargetsNumber();
    if (nt<2) {return false;}
    int target = singleChoice(duel,card);
    if (target==-1) {return false;}
    else
    {
        Card* targetCard = duel->getCardFromCopyId(target);
        if (targetCard == nullptr || !this->getTargetList()->isPresent(targetCard)) {return false;}
        this->spellFromHandLog(duel,card);
        this->spellCost(card);
        short atk = 0;
        if (!targetCard->getIsSpellImmune())
        {

            for (short i=0; i<nt;i++)
            {
                if (targets->at(i)!=targetCard)
                {
                    atk+=targets->at(i)->getAttack();
                    targets->at(i)->setAttacks(0);
                }
            }
            this->getCardTargets()->push_back(targetCard);
            this->getNumericValues()->push_back(atk);
            duel->changeStats(targetCard,atk,0);
            duel->addTurnEndLingeringEffect(card);
        }
        else duel->appendSILog(card,targetCard);
        return true;
    }
}
void Magnetize::onTurnEnd(Duel* duel, Card* card)
{
    if (this->getCardTargets()->size() == 0 || this->getNumericValues()->size() == 0) {return;}
    Card* target = this->getCardTargets()->at(0);
    int atkChange = this->getNumericValues()->at(0);

    if (target->getPlace()==2)
    {
        this->effectLog(duel, card);
        duel->changeStats(target, -atkChange, 0);
    }
    this->getCardTargets()->clear();
    this->getNumericValues()->clear();
}


