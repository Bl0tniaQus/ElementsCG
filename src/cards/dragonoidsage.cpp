#include "dragonoidsage.h"
#include "../duel.h"
#include "../card.h"
void DragonoidSage::onSummon(Duel* duel, Card* card){}
void DragonoidSage::onSpell(Duel* duel, Card* card) {}
void DragonoidSage::onDestroy(Duel* duel, Card* card) {}
void DragonoidSage::onAttack(Duel* duel, Card* card) {}
void DragonoidSage::onDefence(Duel* duel, Card* card) {}
void DragonoidSage::onTurnEnd(Duel* duel, Card* card) {
    if (duel->getPlayer(duel->getTurnPlayer())==card->getOwner())
    {card->getOwner()->changeMana(2);}
}
