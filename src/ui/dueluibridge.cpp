#include "dueluibridge.h"
#include "../engine/duel.h"
#include "../engine/card.h"
#include "../engine/bot.h"
#include <QDebug>
DuelUiBridge::DuelUiBridge()
{


}

void DuelUiBridge::duelControl(Deck* deck0, Deck* deck1)
{
    this->duel->startDuel(deck0,deck1);
    this->updateBoard();
}
void DuelUiBridge::initiateDuel()
{
    Deck deck(1);
    Deck deck2(2);
    duelControl(&deck,&deck2);
}
void DuelUiBridge::playFromHand(short id)
{
    if (duel->getTurnPlayer()==0)
    {
        Player* player = duel->getPlayer(0);
        if (id>=0 && id<player->getHandSize())
        {
            duel->playFromHand(player->getHand()[id]);
            emit handCardPlayed(-1);
            this->updateBoard();
        }

    }
}
void DuelUiBridge::updateBoard()
{
    emit drawHand();
    emit drawSpecialDeck();
    emit drawField();
    emit drawGraveyard();
    emit drawOpponentGraveyard();
    emit drawResources();
}
short DuelUiBridge::makeSpellChoice(Card* card)
{
    emit drawSpellTargets(card);
    mutex->lock(); mutex->lock(); mutex->unlock();
    short id = this->spellTarget;
    this->spellTarget = -2;
    return id;
}
void DuelUiBridge::passTurn()
{
    qDebug()<<"xDDD";
    Player* opponent = this->duel->getPlayer(!this->duel->getTurnPlayer());
    this->duel->passTurn();

    if (opponent->getBot()!=nullptr)
    {
        opponent->getBot()->playTurn(this->duel);
    }
    updateBoard();
}





