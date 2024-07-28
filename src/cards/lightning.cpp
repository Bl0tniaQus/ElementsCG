#include "lightning.h"
#include "../engine/duel.h"
#include "../engine/card.h"
#include "../engine/zone.h"
#include "../engine/bot.h"
bool Lightning::onSpell(Duel* duel, Card* card)
{
        this->spellCostLog(duel, card);
        short mana = card->getOwner()->getMana();
        this->spellCost(card);
        short damage = mana-15;
        if (damage<0) {damage = 0;}
        this->effectLog(duel, card);
        duel->appendLog(duel->lifeChangeLog(card->getOwner()->getOpponent(),-damage),duel->getLastSource());
        card->getOwner()->getOpponent()->changeHp(-damage);

        return true;
}

