#ifndef DUELUIBRIDGE_H
#define DUELUIBRIDGE_H
#include "ui_mainwindow.h"
#include <QLabel>

class Duel;
class DuelUiBridge
{
private:
    Duel* duel;
    Ui::MainWindow* ui;
    QLabel** handImages;
    QLabel** graveyardImages;
    QLabel** opponentGraveyardImages;
    QLabel** specialDeckImages;
    QLabel** playerFieldImages;
    QLabel** playerFieldLabels;
    QLabel** opponentFieldImages;
    QLabel** opponentFieldLabels;
    QLabel** targetImages;
public:
    DuelUiBridge();
    DuelUiBridge(Duel* duel, Ui::MainWindow* ui);
    void setHandImages();
};

#endif
