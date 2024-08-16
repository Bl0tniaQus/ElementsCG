#ifndef DUELUIBRIDGE_H
#define DUELUIBRIDGE_H
#include "cardlabel.h"
#include "../engine/deck.h"
#include <QSemaphore>
class Duel;
class DuelUiBridge : public QObject
{
private:
    Q_OBJECT
    Duel* duel;
    QSemaphore* mutex;
    short spellTarget = -2;
    short materialTarget = -2;
    short attackerTarget = -2;
    short defenderTarget = -2;
    short selectedMaterials = 0;
    int playerDeck = 0;
    int opponentDeck = 0;
public:
    DuelUiBridge();
    void setDuel(Duel* duel) {this->duel=duel;}
    void setMutex(QSemaphore* mtx) {this->mutex = mtx;}
    void setSpellTarget(short t) {this->spellTarget = t;}
    short getSpellTarget() {return this->spellTarget;}
    void setMaterialTarget(short t) {this->materialTarget = t;}
    short getMaterialTarget() {return this->materialTarget;}
    void setAttackerTarget(short t) {this->attackerTarget = t;}
    short getAttackerTarget() {return this->attackerTarget;}
    void setDefenderTarget(short t) {this->defenderTarget = t;}
    short getDefenderTarget() {return this->defenderTarget;}
    void setSelectedMaterials(short m) {this->selectedMaterials = m;}
    short getSelectedMaterials() {return this->selectedMaterials;}
    void duelControl(Deck* deck0, Deck* deck1);
    void updateBoard();
    void endDuel(short result);
    short makeSpellChoice(Card* card);
    short makeSpecialMinionMaterialChoice(Card* card);
    void setDecks(int a, int b) {this->playerDeck = a; this->opponentDeck = b;}
public slots:
    void initiateDuel();
    void playFromHand(short id);
    void playSpecialMinion(short id);
    void battlePhase();
    void passTurn();
signals:
    void drawHand();
    void drawSpecialDeck();
    void drawField();
    void drawResources();
    void drawGraveyard();
    void drawOpponentGraveyard();
    void drawLogs();
    void handCardPlayed(short id = -1);
    void specialMinionPlayed(short id = -1);
    void drawSpellTargets(Card* card);
    void drawAttackers();
    void drawDefenders();
    void drawFirstMaterialTargets(Card* card);
    void drawSecondMaterialTargets(Card* card);
    void drawLastMaterialTargets(Card* card);
    void waitForSpellTarget();
    void duelEndSignal(short result);
};

#endif
