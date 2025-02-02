#include "dueluibridge.h"
#include "../engine/duel.h"
#include "../engine/card.h"
#include "../engine/bot.h"
#include <QDebug>
#include <QThread>
DuelUiBridge::DuelUiBridge()
{


}

void DuelUiBridge::duelControl(Deck* deck0, Deck* deck1)
{
    this->duel->startDuel(deck0,deck1);
    this->updateBoard();
    if (this->duel->getPlayer(this->duel->getTurnPlayer())->getBot()!=nullptr)
    {
        this->delay(200);
        this->duel->getPlayer(this->duel->getTurnPlayer())->getBot()->playTurn(this->duel);

    }
    this->updateBoard();
}
void DuelUiBridge::initiateDuel()
{
    Deck* deck = new Deck(0);
    Deck* deck2 = new Deck(this->opponentDeck);
    this->duelControl(deck,deck2);
    delete deck;
    delete deck2;
}
void DuelUiBridge::playFromHand(short id)
{
    if (this->duel->getTurnPlayer()==0)
    {
        Player* player = this->duel->getPlayer(0);
        if (id>=0 && id<player->getHandSize())
        {
            this->duel->playFromHand(player->getHand()->at(id));
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
            this->duel->summonSpecialMinion(player->getSpecialDeck()->at(id));
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
    emit drawLogs();
    emit drawTurnPlayer();
}
short DuelUiBridge::makeSpellChoice(Card* card)
{
    emit drawSpellTargets(card);
    mutex->acquire(); mutex->acquire(); mutex->release();
    short id = this->spellTarget;
    this->spellTarget = -2;
    return id;
}
short DuelUiBridge::makeSpecialMinionMaterialChoice(Card* card)
{
    short id = -1;
    short n_materials = card->getCardName()->getMaterialNumber();
    if (n_materials == 2 )
    {
        if (this->selectedMaterials==0)
        {
            emit drawFirstMaterialTargets(card);
            mutex->acquire(); mutex->acquire(); mutex->release();
            id = this->materialTarget;
            if (id==-1) {return -1;}
            this->materialTarget = -2;
            this->selectedMaterials = 1;

        }
        else if (this->selectedMaterials==1)
        {
            emit drawLastMaterialTargets(card);
            mutex->acquire(); mutex->acquire(); mutex->release();
            id = this->materialTarget;
            if (id==-1) {return -1;}
            this->materialTarget = -2;
            this->selectedMaterials = 0;
        }
    }
    else if (n_materials == 3)
    {
        if (this->selectedMaterials==0)
        {
            emit drawFirstMaterialTargets(card);
            mutex->acquire(); mutex->acquire(); mutex->release();
            id = this->materialTarget;
            if (id==-1) {return -1;}
            this->materialTarget = -2;
            this->selectedMaterials = 1;

        }
        else if (this->selectedMaterials==1)
        {
            emit drawSecondMaterialTargets(card);
            mutex->acquire(); mutex->acquire(); mutex->release();
            id = this->materialTarget;
            if (id==-1) {return -1;}
            this->materialTarget = -2;
            this->selectedMaterials = 2;
        }
        else if (this->selectedMaterials==2)
        {
            emit drawLastMaterialTargets(card);
            mutex->acquire(); mutex->acquire(); mutex->release();
            id = this->materialTarget;
            if (id==-1) {return -1;}
            this->materialTarget = -2;
            this->selectedMaterials = 0;
        }
    }
    return id;
}

void DuelUiBridge::passTurn()
{
    Player* opponent = this->duel->getPlayer(!this->duel->getTurnPlayer());
    this->duel->passTurn();
    if (opponent->getBot()!=nullptr)
    {
        this->delay(200);
        opponent->getBot()->playTurn(this->duel);
    }
    this->updateBoard();
}
void DuelUiBridge::battlePhase()
{
    short id_attacker, id_defender;
    while (true)
    {
        if (this->duel->getDuelEnded())
        {
            this->attackerTarget = -2;
            this->defenderTarget = -2;
            break;
        }
        this->duel->generateAttackersList();
        this->duel->generateDefendersList();
        emit drawAttackers();
        mutex->acquire(); mutex->acquire(); mutex->release();
        id_attacker = this->attackerTarget;
        if (id_attacker==-1) {break;}
        else if (id_attacker!=-1)
        {
            emit drawDefenders();
            mutex->acquire(); mutex->acquire(); mutex->release();
            id_defender = this->defenderTarget;
            Card* attacker = this->duel->getAttackersList()->getTargetList()->at(id_attacker);
            if (id_defender==10)
            {
                this->duel->directAttack(attacker);
            }
            else if (id_defender!=-1&&id_defender!=10)
            {
                Card* defender = this->duel->getDefendersList()->getTargetList()->at(id_defender);
                this->duel->combat(attacker,defender);
            }
            this->attackerTarget = -2;
            this->defenderTarget = -2;
        }
    this->updateBoard();
    }
}
void DuelUiBridge::endDuel(short result)
{
    if (result!=-1)
    {
        this->updateBoard();
        emit duelEndSignal(result);
    }
}
void DuelUiBridge::delay(int ms)
{
    this->updateBoard();
    QThread::msleep(ms);


}







