#include "tungstenfirefly.h"
#include "../duel.h"
#include "../card.h"
void TungstenFirefly::onSummon(Duel* duel, Card* card){}
void TungstenFirefly::onSpell(Duel* duel, Card* card) {}
void TungstenFirefly::onDestroy(Duel* duel, Card* card) {}
void TungstenFirefly::onAttack(Duel* duel, Card* card) {}
void TungstenFirefly::onDefence(Duel* duel, Card* card) {}
void TungstenFirefly::onTurnEnd(Duel* duel, Card* card) {
    if (duel->getPlayer(duel->getTurnPlayer())==card->getOwner())
    { duel->drawCard(card->getOwner());}
}
