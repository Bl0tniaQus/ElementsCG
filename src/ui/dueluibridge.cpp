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
    if (this->duel->getTurnPlayer()==0)
    {
        Player* player = this->duel->getPlayer(0);
        if (id>=0 && id<player->getHandSize())
        {
            this->duel->playFromHand(player->getHand()[id]);
            emit handCardPlayed(-1);
            this->updateBoard();
        }

    }
}
void DuelUiBridge::playSpecialMinion(short id)
{
    if (this->duel->getTurnPlayer()==0)
    {
        Player* player = this->duel->getPlayer(0);
        if (id>=0 && id<player->getSpecialDeckSize())
        {
            //duel->playFromHand(player->getHand()[id]);
            //emit handCardPlayed(-1);
            qDebug()<<"xd";
            this->duel->summonSpecialMinion(player->getSpecialDeck()[id]);
            emit specialMinionPlayed(-1);
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
    Player* opponent = this->duel->getPlayer(!this->duel->getTurnPlayer());
    this->duel->passTurn();

    if (opponent->getBot()!=nullptr)
    {
        opponent->getBot()->playTurn(this->duel);
    }
    updateBoard();
}





