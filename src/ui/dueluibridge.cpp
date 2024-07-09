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
    this->handImages = new QLabel* [0];
}
void DuelUiBridge::setHandImages()
{
    Player* player = duel->getPlayer(0);
    short n_hand = player->getHandSize();
    std::cout<<n_hand;
    delete [] this->handImages;
    this->handImages = new QLabel* [n_hand];
    int i;
    for (i=0;i<n_hand;i++)
    {
        char* img = player->getHand()[i]->getCardName()->getImage();
        QString imgName = QString::fromStdString(std::string("/:")+std::string(img));
        QPixmap pm(imgName);
        handImages[i] = new QLabel(this->ui->scrollArea);
        handImages[i]->setPixmap(pm);
        handImages[i]->setGeometry(QRect(i*80,0,80,80));
        handImages[i]->setScaledContents(true);
        handImages[i]->setVisible(true);
        handImages[i]->setContentsMargins(10,10,10,10);
    }
    ui->scrollAreaWidgetContents->setGeometry(20,20,i*80,80);
}

