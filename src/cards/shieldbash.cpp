#include "shieldbash.h"
#include "../engine/duel.h"
#include "../engine/card.h"
#include "../engine/zone.h"
#include "../engine/bot.h"
bool ShieldBash::onSpell(Duel* duel, Card* card)
{
    this->getOnSpellTargetList(duel, card);
    Card** targets = this->getTargetList()->getTargetList();
    short target = singleChoice(duel,card);
    if (target==-1) {return false;}
    else
    {
        this->spellCostLog(duel, card);
        this->spellCost(card);
        Card* targetCard = targets[target];
        if (!targetCard->getIsSpellImmune())
        {
        short dmg = targetCard->getDefence();
        card->getOwner()->getOpponent()->changeHp(-dmg);
        this->setTargetList(nullptr,0);
        }
        return true;
    }
}
void ShieldBash::getOnSpellTargetList(Duel* duel, Card* card)
{
    this->minionsOnYourFieldWithSameElement(duel, card,"Earth");
}

