#include "lightning.h"
#include "../engine/duel.h"
#include "../engine/card.h"
#include "../engine/zone.h"
#include "../engine/bot.h"
bool Lightning::onSpell(Duel* duel, Card* card)
{
        this->spellFromHandLog(duel,card);
        this->spellCost(card);
        short mana = card->getOwner()->getMana();
        short damage = mana-15;
        if (damage<0) {damage = 0;}
        this->effectLog(duel, card);
        card->getOwner()->getOpponent()->changeHp(-damage);

        return true;
}

