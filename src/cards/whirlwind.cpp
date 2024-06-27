#include "whirlwind.h"
#include "../duel.h"
#include "../card.h"
void Whirlwind::onSummon(Duel* duel, Card* card){}
void Whirlwind::onSpell(Duel* duel, Card* card)
{

    bool usable = duel->checkEffectRequirements(card);
    if (usable)
    {
        Card** targets = duel->getTargetList().getTargetList();
        int target;
        for (int i=0;i<duel->getTargetList().getTargetsNumber();i++)
        {
            std::cout<<i<<" - "<<targets[i]->getName()<<std::endl;
        }
        std::cout<<"Target: ";
        std::cin>>target;
        Card* targetCard = targets[target];
        duel->toHand(targetCard);
    }
}
void Whirlwind::onDestroy(Duel* duel, Card* card) {}
void Whirlwind::onAttack(Duel* duel, Card* card) {}
void Whirlwind::onDefence(Duel* duel, Card* card) {}
void Whirlwind::onTurnEnd(Duel* duel, Card* card) {}
