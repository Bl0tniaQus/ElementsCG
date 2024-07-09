#include "dueluibridge.h"
#include "../engine/duel.h"
#include "../engine/card.h"
#include <QPixmap>
#include "ui_mainwindow.h"
#include <iostream>
DuelUiBridge::DuelUiBridge(Duel* duel, Ui::MainWindow* ui)
{
    this->duel = duel;
    this->ui = ui;
    this->handImages = new CardLabel* [0];
}
void DuelUiBridge::setHandImages()
{
    Player* player = duel->getPlayer(0);
    short n_hand = player->getHandSize();

    delete [] this->handImages;
    this->handImages = new CardLabel* [n_hand];
    int i;
    for (i=0;i<n_hand;i++)
    {

        char* img = player->getHand()[i]->getCardName()->getImage();
        QString imgName = QString::fromStdString(std::string(":/")+std::string(img));
        QPixmap pm(imgName);
        handImages[i] = new CardLabel;
        handImages[i]->setParent(this->ui->scrollArea);
        handImages[i]->setMainWindowUi(this->ui);
        handImages[i]->setCard(img);
        handImages[i]->setId(i);
        handImages[i]->setStyleSheet("border:none;");
        handImages[i]->setPixmap(pm);
        handImages[i]->setScaledContents(true);
        handImages[i]->setMouseTracking(true);
        handImages[i]->setFrameShape(QFrame::Box);
        handImages[i]->setVisible(true);
        handImages[i]->setGeometry((i*80)+15,15,80,80);
        handImages[i]->setContentsMargins(10,0,10,0);
    }
    ui->scrollAreaWidgetContents->setGeometry(40,40,i*80,200);
}
void DuelUiBridge::duelControl(Deck* deck0, Deck* deck1)
{
    this->duel->DuelControlGui(deck0, deck1);
}

