#include "disassembly.h"
#include "../engine/duel.h"
#include "../engine/card.h"
#include "../engine/zone.h"
#include "../engine/bot.h"
bool Disassembly::onSpell(Duel* duel, Card* card)
{
        short zoneid = duel->getEmptyMinionZone(card->getOwner());
        if (zoneid==-1) {return false;}
        else
        {
                this->spellFromHandLog(duel,card);
                this->spellCost(card);
                duel->summonToken(card, 0, card->getOwner(), zoneid);
                return true;
        }
}

