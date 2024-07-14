#ifndef DUELUIBRIDGE_H
#define DUELUIBRIDGE_H
#include "cardlabel.h"
#include "../engine/deck.h"
#include <QMutex>
class Duel;
class DuelUiBridge : public QObject
{
private:
    Q_OBJECT
    Duel* duel;
    QMutex* mutex;
    short spellTarget = -2;
public:
    DuelUiBridge();
    void setDuel(Duel* duel) {this->duel=duel;}
    void setMutex(QMutex* mtx) {this->mutex = mtx;}
    void setSpellTarget(short t) {this->spellTarget = t;}
    short getSpellTarget() {return this->spellTarget;}
    void duelControl(Deck* deck0, Deck* deck1);
    void updateBoard();
    short makeSpellChoice(Card* card);
public slots:
    void initiateDuel();
    void playFromHand(short id);
    void passTurn();
signals:
    void drawHand();
    void drawSpecialDeck();
    void drawField();
    void drawResources();
    void drawGraveyard();
    void drawOpponentGraveyard();
    void handCardPlayed(short id = -1);
    void drawSpellTargets(Card* card);
    void waitForSpellTarget();
};

#endif
