#include "disassembly.h"
#include "../engine/duel.h"
#include "../engine/card.h"
#include "../engine/zone.h"
#include "../engine/bot.h"
bool Disassembly::onSpell(Duel* duel, Card* card)
{
        this->specialMinionsOnYourFieldSpecialSummonedWithElement(duel,card->getOwner(),"Earth");
        short n = this->getTargetList()->getTargetsNumber();
        if (n<1) {return false;}
        //std::vector<Card*>* targets = this->getTargetList()->getTargetList();
        int target = singleChoice(duel,card);
        if (target==-1) {return false;}
        else
        {
                short zoneid = duel->getEmptyMinionZone(card->getOwner());
                if (zoneid==-1) {return false;}
                else
                {
                        Card* targetCard = duel->getCardFromCopyId(target);
                        if (targetCard == nullptr || !this->getTargetList()->isPresent(targetCard)) {return false;}
                        this->spellFromHandLog(duel,card);
                        this->spellCost(card);
                        duel->changeStats(targetCard,-2,-2);
                        std::vector<Card*> materials = std::vector<Card*>(*targetCard->getCardName()->getUsedMaterials());
                        materials = TargetList::filterOneElement(materials, "Earth");
                        this->setTargetList(materials);
                        short lvl = this->highestOriginalLevelInTargetList();
                        duel->summonToken(card, 0, card->getOwner(), zoneid);
                        duel->changeLevel(card->getOwner()->getMinionField()[zoneid].getCard(),lvl);
                        return true;
                }
        }
}

