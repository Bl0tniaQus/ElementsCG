#include "dragonoidscout.h"
#include "../duel.h"
#include "../card.h"
void DragonoidScout::onSummon(Duel* duel, Card* card)
{
    duel->drawCard(card->getOwner());
}
void DragonoidScout::onSpell(Duel* duel, Card* card) {}
void DragonoidScout::onDestroy(Duel* duel, Card* card) {}
void DragonoidScout::onAttack(Duel* duel, Card* card) {}
void DragonoidScout::onDefence(Duel* duel, Card* card) {}
void DragonoidScout::onTurnEnd(Duel* duel, Card* card) {}
