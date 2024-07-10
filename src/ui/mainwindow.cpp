#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "../engine/globals.h"
#include "../engine/card.h"
#include <iostream>
#include <QDebug>
MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow), duelThread(this)
{
    this->ui->setupUi(this);
    this->setFixedSize(1600,900);
    this->ui->stackedWidget->setCurrentIndex(0);
    this->handImages = new CardLabel* [0];
    this->duel = new Duel;

    this->duel->getPlayer(1)->setBot(&bot);
    this->bridge.setDuel(duel);

    connect(this->ui->testButton, &QPushButton::released, this, &MainWindow::startDuel);
    connect(&this->bridge,&DuelUiBridge::drawHand, this, &MainWindow::setHandImages);
    connect(this, &MainWindow::duelStartSignal, &this->bridge, &DuelUiBridge::initiateDuel);
    connect(this->ui->playFromHandButton, &QPushButton::released, this, &MainWindow::playFromHand);
    connect(this, &MainWindow::handAction, &this->bridge, &DuelUiBridge::playFromHand);
    connect(&this->bridge,&DuelUiBridge::handCardPlayed,this, &MainWindow::handTarget);
    this->bridge.moveToThread(&duelThread);
    duelThread.start();
    emit duelStartSignal();








}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::startDuel()
{


    this->ui->stackedWidget->setCurrentIndex(1);

    //ui->scrollAreaWidgetContents->setContentsMargins(20,20,20,20);
    //label->setFrameStyle(QFrame::Panel | QFrame::Sunken);
   // label->setAlignment(Qt::AlignBottom | Qt::AlignRight);
    //label->setParent(ui->scrollArea);
    //this->ui->oppZ0Image->setPixmap(pm);
   // label->setText("test");
   // label->setVisible(true);
   // label->setGeometry(QRect(10,10,30,80));

   // this->ui->oppZ0Image->setPixmap(empty);
    //this->ui->oppZ0Label->setText("L10 10/10 B1 A1 SI N");
    //this->ui->oppZ0Image->setScaledContents(true);

}
void MainWindow::setHandImages()
{
    Player* player = duel->getPlayer(0);
    short n_hand = player->getHandSize();
    int i;
    QPixmap empty;
    for (i=0; i<this->handSize;i++)
    {
        this->handImages[i]->setStyleSheet("background:none;");
        this->handImages[i]->setPixmap(empty);
        delete this->handImages[i];
    }
    delete [] this->handImages;
    this->handImages = new CardLabel* [n_hand];
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
        handImages[i]->setContentsMargins(0,0,0,0);

        connect(handImages[i],&CardLabel::handCardHighlight, this, &MainWindow::handTarget);
    }
    ui->scrollAreaWidgetContents->setGeometry(40,40,i*80,200);
    this->handSize = n_hand;
}
void MainWindow::handTarget(short id)
{
    this->selectedHandCard = id;
    short handSize = this->duel->getPlayer(0)->getHandSize();
        for (int i=0;i<handSize;i++)
        {
            this->handImages[i]->setStyleSheet("border:none;");
        }
        if (id!=-1)
        {
            this->handImages[id]->setStyleSheet("border: 3px solid red;");
        }
}
void MainWindow::playFromHand()
{
    if (this->selectedHandCard!=-1)
    {
        emit handAction(this->selectedHandCard);
    }
}

