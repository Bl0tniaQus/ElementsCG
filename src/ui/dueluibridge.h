#ifndef DUELUIBRIDGE_H
#define DUELUIBRIDGE_H
#include "ui_mainwindow.h"
#include "cardlabel.h"
#include "../engine/deck.h"
class Duel;
class DuelUiBridge : public QObject
{
private:
    Q_OBJECT
    Duel* duel;
    Ui::MainWindow* ui;
    CardLabel** handImages;
    CardLabel** graveyardImages;
    CardLabel** opponentGraveyardImages;
    CardLabel** specialDeckImages;
    CardLabel** playerFieldImages;
    CardLabel** playerFieldLabels;
    CardLabel** opponentFieldImages;
    CardLabel** opponentFieldLabels;
    CardLabel** targetImages;
public:
    DuelUiBridge();
    DuelUiBridge(Duel* duel, Ui::MainWindow* ui);
    void setHandImages();
    void duelControl(Deck* deck0, Deck* deck1);
};

#endif
