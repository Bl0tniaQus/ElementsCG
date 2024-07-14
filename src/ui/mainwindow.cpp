#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "../engine/globals.h"
#include "../engine/card.h"
#include "../engine/zone.h"
#include <iostream>
#include <QDebug>
MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow), duelThread(this)
{
    this->ui->setupUi(this);
    this->setFixedSize(1600,900);
    this->ui->stackedWidget->setCurrentIndex(0);
    connect(this->ui->testButton, &QPushButton::released, this, &MainWindow::startDuel);

}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::startDuel()
{
    this->ui->targetGroupBox->setVisible(false);
    this->bridge = new DuelUiBridge;
    this->duel = new Duel;
    this->duel->getPlayer(1)->setBot(&bot);
    this->bridge->setDuel(duel);
    this->duel->setUiBridge(this->bridge);
    this->bridge->setMutex(&mutex);
    connect(this->bridge,&DuelUiBridge::drawHand, this, &MainWindow::setHandImages);
    connect(this->bridge,&DuelUiBridge::drawGraveyard, this, &MainWindow::setGraveyardImages);
    connect(this->bridge,&DuelUiBridge::drawOpponentGraveyard, this, &MainWindow::setOpponentGraveyardImages);
    connect(this->bridge,&DuelUiBridge::drawSpecialDeck, this, &MainWindow::setSpecialDeckImages);
    connect(this->bridge,&DuelUiBridge::drawField, this, &MainWindow::setFieldImagesAndLabels);
    connect(this->bridge,&DuelUiBridge::drawResources, this, &MainWindow::setResources);
    connect(this->bridge,&DuelUiBridge::drawSpellTargets, this, &MainWindow::setTargetImages);
    connect(this->ui->cardTabs, &QTabWidget::currentChanged, this, &MainWindow::clearTabs);
    connect(this, &MainWindow::duelStartSignal, this->bridge, &DuelUiBridge::initiateDuel);
    connect(this->ui->playFromHandButton, &QPushButton::released, this, &MainWindow::playFromHand);
    connect(this->ui->playSpecialMinionButton, &QPushButton::released, this, &MainWindow::playSpecialMinion);
    connect(this, &MainWindow::handAction, this->bridge, &DuelUiBridge::playFromHand);
    connect(this, &MainWindow::specialDeckAction, this->bridge, &DuelUiBridge::playSpecialMinion);
    connect(this, &MainWindow::turnEndSignal, this->bridge, &DuelUiBridge::passTurn);
    connect(this->bridge,&DuelUiBridge::handCardPlayed,this, &MainWindow::handTarget);
    connect(this->bridge,&DuelUiBridge::specialMinionPlayed,this, &MainWindow::specialDeckTarget);

    connect(this->ui->endTurnButton, &QPushButton::released, this, &MainWindow::turnEnd);

    this->bridge->moveToThread(&duelThread);
    duelThread.start();

    this->ui->stackedWidget->setCurrentIndex(1);
    this->handImages = new CardLabel* [0];
    this->targetImages = new CardLabel* [0];
    this->specialDeckImages = new CardLabel* [0];
    this->graveyardImages = new CardLabel* [0];
    this->opponentGraveyardImages = new CardLabel* [0];
    this->playerFieldImages = new CardLabel* [5];
    this->playerFieldLabels = new CardLabel* [5];
    this->opponentFieldImages = new CardLabel* [5];
    this->opponentFieldLabels = new CardLabel* [5];

    for (int i=0;i<5;i++)
    {
        this->playerFieldImages[i] = new CardLabel;
        this->playerFieldLabels[i] = new CardLabel;
        this->opponentFieldImages[i] = new CardLabel;
        this->opponentFieldLabels[i] = new CardLabel;
    }
    emit duelStartSignal();
}
void MainWindow::setHandImages()
{
    this->selectedHandCard = -1;
    Player* player = duel->getPlayer(0);
    short n_hand = player->getHandSize();
    int i;
    for (i=0; i<this->handSize;i++)
    {
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
        handImages[i]->setParent(this->ui->handCardsAreaContents);
        handImages[i]->setMainWindowUi(this->ui);
        handImages[i]->setCard(img);
        handImages[i]->setPlace(1);
        handImages[i]->setId(i);
        handImages[i]->setHasImage(true);
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
    ui->handCardsAreaContents->setGeometry(40,40,(i*80)+15,200);
    this->handSize = n_hand;
}
void MainWindow::setSpecialDeckImages()
{
    this->selectedSpecialDeckCard = -1;
    Player* player = duel->getPlayer(0);
    short n_special = player->getSpecialDeckSize();
    int i;
    QPixmap empty;
    for (i=0; i<this->specialDeckSize;i++)
    {
        delete this->specialDeckImages[i];
    }
    delete [] this->specialDeckImages;
    this->specialDeckImages = new CardLabel* [n_special];
    for (i=0;i<n_special;i++)
    {
        char* img = player->getSpecialDeck()[i]->getCardName()->getImage();
        QString imgName = QString::fromStdString(std::string(":/")+std::string(img));
        QPixmap pm(imgName);
        specialDeckImages[i] = new CardLabel;
        specialDeckImages[i]->setParent(this->ui->specialDeckCardsAreaContents);
        specialDeckImages[i]->setMainWindowUi(this->ui);
        specialDeckImages[i]->setCard(img);
        specialDeckImages[i]->setPlace(4);
        specialDeckImages[i]->setId(i);
        specialDeckImages[i]->setHasImage(i);
        specialDeckImages[i]->setStyleSheet("border:none;");
        specialDeckImages[i]->setPixmap(pm);
        specialDeckImages[i]->setScaledContents(true);
        specialDeckImages[i]->setMouseTracking(true);
        specialDeckImages[i]->setFrameShape(QFrame::Box);
        specialDeckImages[i]->setVisible(true);
        specialDeckImages[i]->setGeometry((i*80)+15,15,80,80);
        specialDeckImages[i]->setContentsMargins(0,0,0,0);

        connect(specialDeckImages[i],&CardLabel::specialDeckCardHighlight, this, &MainWindow::specialDeckTarget);
    }
    ui->specialDeckCardsAreaContents->setGeometry(40,40,(i*80)+15,200);
    this->specialDeckSize = n_special;
}
void MainWindow::setGraveyardImages()
{
    Player* player = duel->getPlayer(0);
    short n_graveyard = player->getGraveyardSize();
    this->ui->graveyardCountLabel->setText(QString::number(n_graveyard));
    int i;
    for (i=0; i<this->graveyardSize;i++)
    {
        delete this->graveyardImages[i];
    }
    delete [] this->graveyardImages;
    this->graveyardImages = new CardLabel* [n_graveyard];
    for (i=0;i<n_graveyard;i++)
    {
        char* img = player->getGraveyard()[i]->getCardName()->getImage();
        QString imgName = QString::fromStdString(std::string(":/")+std::string(img));
        QPixmap pm(imgName);
        graveyardImages[i] = new CardLabel;
        graveyardImages[i]->setParent(this->ui->graveyardCardsAreaContents);
        graveyardImages[i]->setMainWindowUi(this->ui);
        graveyardImages[i]->setCard(img);
        graveyardImages[i]->setPlace(3);
        graveyardImages[i]->setId(i);
        graveyardImages[i]->setHasImage(true);
        graveyardImages[i]->setStyleSheet("border:none;");
        graveyardImages[i]->setPixmap(pm);
        graveyardImages[i]->setScaledContents(true);
        graveyardImages[i]->setMouseTracking(true);
        graveyardImages[i]->setFrameShape(QFrame::Box);
        graveyardImages[i]->setVisible(true);
        graveyardImages[i]->setGeometry((i*80)+15,15,80,80);
        graveyardImages[i]->setContentsMargins(0,0,0,0);
    }
    ui->graveyardCardsAreaContents->setGeometry(40,40,(i*80)+15,200);
    this->graveyardSize = n_graveyard;
}
void MainWindow::setOpponentGraveyardImages()
{
    Player* opponent = duel->getPlayer(1);
    short n_graveyard = opponent->getGraveyardSize();
    this->ui->opponentGraveyardCountLabel->setText(QString::number(n_graveyard));
    int i;
    for (i=0; i<this->opponentGraveyardSize;i++)
    {
        delete this->opponentGraveyardImages[i];
    }
    delete [] this->opponentGraveyardImages;
    this->opponentGraveyardImages = new CardLabel* [n_graveyard];
    for (i=0;i<n_graveyard;i++)
    {
        char* img = opponent->getGraveyard()[i]->getCardName()->getImage();
        QString imgName = QString::fromStdString(std::string(":/")+std::string(img));
        QPixmap pm(imgName);
        opponentGraveyardImages[i] = new CardLabel;
        opponentGraveyardImages[i]->setParent(this->ui->opponentGraveyardCardsAreaContents);
        opponentGraveyardImages[i]->setMainWindowUi(this->ui);
        opponentGraveyardImages[i]->setCard(img);
        opponentGraveyardImages[i]->setPlace(3);
        opponentGraveyardImages[i]->setId(i);
        opponentGraveyardImages[i]->setHasImage(true);
        opponentGraveyardImages[i]->setStyleSheet("border:none;");
        opponentGraveyardImages[i]->setPixmap(pm);
        opponentGraveyardImages[i]->setScaledContents(true);
        opponentGraveyardImages[i]->setMouseTracking(true);
        opponentGraveyardImages[i]->setFrameShape(QFrame::Box);
        opponentGraveyardImages[i]->setVisible(true);
        opponentGraveyardImages[i]->setGeometry((i*80)+15,15,80,80);
        opponentGraveyardImages[i]->setContentsMargins(0,0,0,0);
    }
    ui->opponentGraveyardCardsAreaContents->setGeometry(40,40,(i*80)+15,200);
    this->opponentGraveyardSize = n_graveyard;
}
void MainWindow::handTarget(short id)
{
    if (!targeting)
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
}
void MainWindow::specialDeckTarget(short id)
{
    if (!targeting)
    {
    this->selectedSpecialDeckCard = id;
    short sd_size = this->duel->getPlayer(0)->getSpecialDeckSize();
        for (int i=0;i<sd_size;i++)
        {
            this->specialDeckImages[i]->setStyleSheet("border:none;");
        }
        if (id!=-1)
        {
            this->specialDeckImages[id]->setStyleSheet("border: 3px solid red;");
        }
    }
}
void MainWindow::targetingTarget(short id)
{
    if (targeting)
    {
    this->selectedSpellTarget = id;
        for (int i=0;i<this->n_targets;i++)
        {
            this->targetImages[i]->setStyleSheet("border:none;");
        }
        if (id!=-1)
        {
            this->targetImages[id]->setStyleSheet("border: 3px solid red;");
        }
    }
}
void MainWindow::playFromHand()
{
    if (this->selectedHandCard!=-1&&!targeting)
    {
        emit handAction(this->selectedHandCard);
    }
}
void MainWindow::playSpecialMinion()
{
    if (this->selectedSpecialDeckCard!=-1&&!targeting)
    {
        emit specialDeckAction(this->selectedSpecialDeckCard);
    }
}
void MainWindow::setFieldImagesAndLabels()
{

    Player* player1 = duel->getPlayer(0);
    Player* player2 = duel->getPlayer(1);
    Zone *playerField = player1->getMinionField();
    Zone *opponentField = player2->getMinionField();
    Card* cardPlayer;
    Card* cardOpp;
    int i;

    for (i = 0; i<5;i++)
    {
       delete this->playerFieldImages[i];
       delete this->playerFieldLabels[i];
       delete this->opponentFieldImages[i];
       delete this->opponentFieldLabels[i];

    }
       delete[] this->playerFieldImages;
       delete[] this->playerFieldLabels;
       delete[] this->opponentFieldImages;
       delete[] this->opponentFieldLabels;
    this->playerFieldImages = new CardLabel* [5];
    this->playerFieldLabels = new CardLabel* [5];
    this->opponentFieldImages = new CardLabel* [5];
    this->opponentFieldLabels = new CardLabel* [5];
    for (i=0; i<5; i++)
    {
        cardPlayer = playerField[i].getCard();
        cardOpp = opponentField[4-i].getCard();
        playerFieldImages[i] = new CardLabel;
        playerFieldImages[i]->setParent(this->ui->playerFieldFrame);
        playerFieldImages[i]->setMainWindowUi(this->ui);
        playerFieldImages[i]->setStyleSheet("border:none;");
        playerFieldImages[i]->setScaledContents(true);
        playerFieldImages[i]->setPlace(2);
        playerFieldImages[i]->setMouseTracking(true);
        playerFieldImages[i]->setFrameShape(QFrame::Box);
        playerFieldImages[i]->setVisible(true);
        playerFieldImages[i]->setGeometry((i*120)+15,15,120,120);
        playerFieldImages[i]->setContentsMargins(0,0,0,0);

        playerFieldLabels[i] = new CardLabel;
        playerFieldLabels[i]->setParent(this->ui->playerFieldLabelsFrame);
        playerFieldLabels[i]->setMainWindowUi(this->ui);
        playerFieldLabels[i]->setStyleSheet("border:none;");
        playerFieldLabels[i]->setScaledContents(true);
        playerFieldLabels[i]->setPlace(2);
        playerFieldLabels[i]->setMouseTracking(true);
        playerFieldLabels[i]->setFrameShape(QFrame::Box);
        playerFieldLabels[i]->setVisible(true);
        playerFieldLabels[i]->setGeometry((i*120)+15,15,120,20);
        playerFieldLabels[i]->setContentsMargins(0,0,0,0);



        opponentFieldImages[4-i] = new CardLabel;
        opponentFieldImages[4-i]->setParent(this->ui->opponentFieldFrame);
        opponentFieldImages[4-i]->setMainWindowUi(this->ui);
        opponentFieldImages[4-i]->setStyleSheet("border:none;");
        opponentFieldImages[4-i]->setScaledContents(true);
        opponentFieldImages[4-i]->setPlace(2);
        opponentFieldImages[4-i]->setMouseTracking(true);
        opponentFieldImages[4-i]->setFrameShape(QFrame::Box);
        opponentFieldImages[4-i]->setVisible(true);
        opponentFieldImages[4-i]->setGeometry((i*120)+15,15,120,120);
        opponentFieldImages[4-i]->setContentsMargins(0,0,0,0);

        opponentFieldLabels[4-i] = new CardLabel;
        opponentFieldLabels[4-i]->setParent(this->ui->opponentFieldLabelsFrame);
        opponentFieldLabels[4-i]->setMainWindowUi(this->ui);
        opponentFieldLabels[4-i]->setStyleSheet("border:none;");
        opponentFieldLabels[4-i]->setScaledContents(true);
        opponentFieldLabels[4-i]->setPlace(2);
        opponentFieldLabels[4-i]->setMouseTracking(true);
        opponentFieldLabels[4-i]->setFrameShape(QFrame::Box);
        opponentFieldLabels[4-i]->setVisible(true);
        opponentFieldLabels[4-i]->setGeometry((i*120)+15,15,120,20);
        opponentFieldLabels[4-i]->setContentsMargins(0,0,0,0);

        if (cardPlayer!=nullptr)
        {
            char* img = cardPlayer->getCardName()->getImage();
            QString imgName = QString::fromStdString(std::string(":/")+std::string(img));
            QPixmap pm(imgName);
            playerFieldImages[i]->setCard(img);
            playerFieldImages[i]->setId(i);
            playerFieldImages[i]->setPixmap(pm);
            playerFieldImages[i]->setHasImage(true);
            playerFieldLabels[i]->setCard(img);

            short atk = cardPlayer->getAttack();
            short def = cardPlayer->getDefence();
            short lvl = cardPlayer->getLevel();
            short br = cardPlayer->getBarrier();
            short negated = cardPlayer->getIsNegated();
            short attacks = cardPlayer->getAttacks();
            short si = cardPlayer->getIsSpellImmune();
            //L10 10/10 B1 A1 SI N
            std::string str = "L"+std::to_string(lvl);
            str += " "+std::to_string(atk)+"/"+std::to_string(def);
            str += " A"+std::to_string(attacks);
            if (br>0){str += " B"+std::to_string(br);}
            if (si>0){str += " SI";}
            if (negated>0){str += " N";}
            playerFieldLabels[i]->setText(QString::fromStdString(str));
        }
        if (cardOpp!=nullptr)
        {
            char* img = cardOpp->getCardName()->getImage();
            QString imgName = QString::fromStdString(std::string(":/")+std::string(img));
            QPixmap pm(imgName);
            opponentFieldImages[4-i]->setCard(img);
            opponentFieldImages[4-i]->setId(i);
            opponentFieldImages[4-i]->setPixmap(pm);
            opponentFieldImages[4-i]->setHasImage(true);

            short atk = cardOpp->getAttack();
            short def = cardOpp->getDefence();
            short lvl = cardOpp->getLevel();
            short br = cardOpp->getBarrier();
            short negated = cardOpp->getIsNegated();
            short attacks = cardOpp->getAttacks();
            short si = cardOpp->getIsSpellImmune();
            //L10 10/10 B1 A1 SI N
            std::string str = "L"+std::to_string(lvl);
            str += " "+std::to_string(atk)+"/"+std::to_string(def);
            str += " A"+std::to_string(attacks);
            if (br>0){str += " B"+std::to_string(br);}
            if (si>0){str += " SI";}
            if (negated>0){str += " N";}

            opponentFieldLabels[4-i]->setText(QString::fromStdString(str));
        }
    }
}
void MainWindow::setResources()
{
    Player* player = this->duel->getPlayer(0);
    Player* opponent = this->duel->getPlayer(1);

    ui->playerName->setText(QString(player->getName()));
    ui->playerLifeValue->setText(QString::number(player->getHp()));
    ui->playerManaValue->setText(QString::number(player->getMana()));
    ui->playerDeckCount->setText(QString::number(player->getDeckSize()));
    ui->playerSummonLimitValue->setText(QString::number(player->getSummonLimit()));

    ui->opponentName->setText(QString(opponent->getName()));
    ui->opponentLifeValue->setText(QString::number(opponent->getHp()));
    ui->opponentManaValue->setText(QString::number(opponent->getMana()));
    ui->opponentDeckCount->setText(QString::number(opponent->getDeckSize()));
    ui->opponentSpecialDeckCount->setText(QString::number(opponent->getSpecialDeckSize()));
    ui->opponentHandCount->setText(QString::number(opponent->getHandSize()));
    ui->opponentSummonLimitValue->setText(QString::number(opponent->getSummonLimit()));
}
void MainWindow::setTargetImages(Card* card)
{
    Card** targets = card->getCardName()->getTargetList()->getTargetList();
    short nt = card->getCardName()->getTargetList()->getTargetsNumber();
    Card* c;
    int i;
    if (nt>0) {
        this->targeting = true;
        this->ui->targetGroupBox->setVisible(true);
        connect(this->ui->confirmTargetButton, &QPushButton::released, this, &MainWindow::spellConfirm);
        connect(this->ui->cancelTargetButton, &QPushButton::released, this, &MainWindow::spellCancel);
    }
    for (i=0;i<this->n_targets;i++)
    {
        delete this->targetImages[i];
    }
    delete [] this->targetImages;
    this->targetImages = new CardLabel* [nt];
    for (i=0;i<nt;i++)
    {
        c = targets[i];
        char* img = c->getCardName()->getImage();
        QString imgName = QString::fromStdString(std::string(":/")+std::string(img));
        QPixmap pm(imgName);
        this->targetImages[i] = new CardLabel;
        this->targetImages[i]->setParent(this->ui->targetsArea);
        this->targetImages[i]->setMainWindowUi(this->ui);
        this->targetImages[i]->setCard(img);
        this->targetImages[i]->setPlace(5);
        this->targetImages[i]->setId(i);
        this->targetImages[i]->setStyleSheet("border:none;");
        this->targetImages[i]->setPixmap(pm);
        this->targetImages[i]->setScaledContents(true);
        this->targetImages[i]->setMouseTracking(true);
        this->targetImages[i]->setFrameShape(QFrame::Box);
        this->targetImages[i]->setVisible(true);
        this->targetImages[i]->setGeometry((i*80)+15,15,80,80);
        this->targetImages[i]->setContentsMargins(0,0,0,0);

        connect(targetImages[i],&CardLabel::targetCardHighlight, this, &MainWindow::targetingTarget);

    }
    this->n_targets = nt;
}
void MainWindow::spellConfirm()
{
    if (this->selectedSpellTarget!=-1)
    {
        this->bridge->setSpellTarget(this->selectedSpellTarget);
        this->targeting = false;
        this->selectedSpellTarget = -1;
        disconnect(this->ui->cancelTargetButton, nullptr, nullptr, nullptr);
        disconnect(this->ui->confirmTargetButton, nullptr, nullptr, nullptr);
        clearTargets();
        mutex.unlock();
    }
}
void MainWindow::spellCancel()
{
    this->bridge->setSpellTarget(-1);
    this->targeting = false;
    this->selectedSpellTarget = -1;
    disconnect(this->ui->cancelTargetButton, nullptr, nullptr, nullptr);
    disconnect(this->ui->confirmTargetButton, nullptr, nullptr, nullptr);
    clearTargets();
    mutex.unlock();
}
void MainWindow::clearTargets()
{
    for (int i=0;i<this->n_targets;i++)
    {
        delete this->targetImages[i];
    }
    delete [] this->targetImages;
    this->n_targets = 0;
    this->targetImages = new CardLabel* [0];
    this->selectedSpellTarget = -1;
    this->ui->targetGroupBox->setVisible(false);
}
void MainWindow::clearTabs()
{
    this->selectedHandCard = -1;
    this->selectedSpellTarget = -1;
    this->selectedSpecialDeckCard = -1;
    setHandImages();
    setSpecialDeckImages();
    setGraveyardImages();
    setOpponentGraveyardImages();
}
void MainWindow::turnEnd()
{
        if (this->duel->getTurnPlayer()==0&&!targeting)
        {
            emit turnEndSignal();
        }
}


