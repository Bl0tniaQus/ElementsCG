#ifndef DUELUIBRIDGE_H
#define DUELUIBRIDGE_H
#include "cardlabel.h"
#include "../engine/deck.h"
class Duel;
class DuelUiBridge : public QObject
{
private:
    Q_OBJECT
    Duel* duel;
public:
    DuelUiBridge();
    void setDuel(Duel* duel) {this->duel=duel;}
    void duelControl(Deck* deck0, Deck* deck1);
public slots:
    void initiateDuel();
    void playFromHand(short id);
signals:
    void drawHand();
    void drawField();
    void handCardPlayed(short id = -1);
};

#endif
