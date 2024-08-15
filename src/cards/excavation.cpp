#include "excavation.h"
#include "../engine/duel.h"
#include "../engine/card.h"
#include "../engine/zone.h"
#include "../engine/bot.h"
bool Excavation::onSpell(Duel* duel, Card* card)
{
    if (card->getOwner()->getDeckSize()<3) {return false;}
    this->spellFromHandLog(duel,card);
    this->spellCost(card);
    this->getOnSpellTargetList(duel, card);
    short n_revealed = this->getTargetList()->getTargetsNumber();
    Card** revealed = this->getTargetList()->getTargetList();
    for (short i = 0; i<n_revealed; i++)
    {
        duel->excavateCard(revealed[i]);
    }
    duel->updateBoard();
    this->cardsWithSameElementInTargetList("Earth");
    short n = this->getTargetList()->getTargetsNumber();
    Card** targets = this->getTargetList()->getTargetList();
    short target = this->singleChoice(duel, card);
    if (target>-1)
    {
        duel->searchCard(targets[target]);
    }
    return true;
}
void Excavation::getOnSpellTargetList(Duel* duel, Card* card)
{
    this->nTopCardsFromDeck(duel,card,3);
}

