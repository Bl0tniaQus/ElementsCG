#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "../engine/globals.h"
#include "../engine/card.h"
#include "../engine/zone.h"
#include <iostream>
#include <QDebug>
#include <QMovie>
#include <QScrollBar>
MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow), duelThread(this)
{
    this->ui->setupUi(this);
    this->loadDecks();
    this->setFixedSize(1600,900);
    this->ui->stackedWidget->setCurrentIndex(0);
    delete this->ui->uselessTabTarget;
    delete this->ui->playerNameUselessTab;
    delete this->ui->opponentNameUselessTab;
    delete this->ui->duelLogUselessTab;
    this->ui->confirmTargetButton->setStyleSheet("font-weight:bold;");
    this->ui->cancelTargetButton->setStyleSheet("font-weight:bold;");
    QPixmap heart = QPixmap(":/life");
    QPixmap mana = QPixmap(":/mana");
    QPixmap hand = QPixmap(":/hand");
    QPixmap spdeck = QPixmap(":/spdeck");
    QPixmap deck = QPixmap(":/deck");
    QPixmap sl = QPixmap(":/summonlimit");
    QMovie* circle = new QMovie(":/spinningcircle");
    QString styles_black = "QToolTip {background-color:#353535; color:white;} *{color:black; font-size:20px; font-weight:bold;}";
    QString styles_white = "QToolTip {background-color:#353535; color:white;} *{color:white; font-size:20px; font-weight:bold;}";
    this->ui->heartPlayer->setScaledContents(true);
    this->ui->heartPlayer->setPixmap(heart);
    this->ui->heartPlayer->setStyleSheet(styles_black);
    this->ui->heartPlayer->setToolTip("Hit points");
    this->ui->manaPlayer->setScaledContents(true);
    this->ui->manaPlayer->setPixmap(mana);
    this->ui->manaPlayer->setStyleSheet(styles_black);
    this->ui->manaPlayer->setToolTip("Mana");
    this->ui->deckPlayer->setScaledContents(true);
    this->ui->deckPlayer->setPixmap(deck);
    this->ui->deckPlayer->setStyleSheet(styles_black);
    this->ui->deckPlayer->setToolTip("Cards in deck");
    this->ui->summonLimitPlayer->setStyleSheet(styles_black);
    this->ui->summonLimitPlayer->setToolTip("Remaining normal summons");
    this->ui->summonLimitPlayer->setScaledContents(true);
    this->ui->summonLimitPlayer->setPixmap(sl);
    this->ui->playerLifeValue->setToolTip("Hit Points");
    this->ui->playerLifeValue->raise();
    this->ui->playerLifeValue->setGeometry(this->ui->heartPlayer->geometry());
    this->ui->playerLifeValue->resize(51,42);
    this->ui->playerLifeValue->setStyleSheet(styles_black);
    this->ui->playerManaValue->setToolTip("Mana");
    this->ui->playerManaValue->raise();
    this->ui->playerManaValue->setGeometry(this->ui->manaPlayer->geometry());
    this->ui->playerManaValue->resize(51,42);
    this->ui->playerManaValue->setStyleSheet(styles_black);
    this->ui->playerDeckCount->setToolTip("Cards in deck");
    this->ui->playerDeckCount->raise();
    this->ui->playerDeckCount->setGeometry(this->ui->deckPlayer->geometry());
    this->ui->playerDeckCount->resize(51,42);
    this->ui->playerDeckCount->setStyleSheet(styles_white);
    this->ui->playerSummonLimitValue->setToolTip("Remaining normal summons");
    this->ui->playerSummonLimitValue->raise();
    this->ui->playerSummonLimitValue->setGeometry(this->ui->summonLimitPlayer->geometry());
    this->ui->playerSummonLimitValue->resize(51,42);
    this->ui->playerSummonLimitValue->setStyleSheet(styles_black);


    this->ui->heartOpponent->setScaledContents(true);
    this->ui->heartOpponent->setPixmap(heart);
    this->ui->heartOpponent->setStyleSheet(styles_black);
    this->ui->heartOpponent->setToolTip("Hit points");
    this->ui->manaOpponent->setScaledContents(true);
    this->ui->manaOpponent->setPixmap(mana);
    this->ui->manaOpponent->setStyleSheet(styles_black);
    this->ui->manaOpponent->setToolTip("Mana");
    this->ui->handOpponent->setScaledContents(true);
    this->ui->handOpponent->setPixmap(hand);
    this->ui->handOpponent->setStyleSheet(styles_black);
    this->ui->handOpponent->setToolTip("Cards in hand");
    this->ui->deckOpponent->setScaledContents(true);
    this->ui->deckOpponent->setPixmap(deck);
    this->ui->deckOpponent->setStyleSheet(styles_black);
    this->ui->deckOpponent->setToolTip("Cards in deck");
    this->ui->specialDeckOpponent->setScaledContents(true);
    this->ui->specialDeckOpponent->setPixmap(spdeck);
    this->ui->specialDeckOpponent->setStyleSheet(styles_black);
    this->ui->specialDeckOpponent->setToolTip("Cards in sp. deck");
    this->ui->summonLimitOpponent->setScaledContents(true);
    this->ui->summonLimitOpponent->setPixmap(sl);
    this->ui->summonLimitOpponent->setStyleSheet(styles_black);
    this->ui->summonLimitOpponent->setToolTip("Remaining normal summons");

    this->ui->opponentLifeValue->setToolTip("Hit points");
    this->ui->opponentLifeValue->raise();
    this->ui->opponentLifeValue->setGeometry(this->ui->heartOpponent->geometry());
    this->ui->opponentLifeValue->resize(51,42);
    this->ui->opponentLifeValue->setStyleSheet(styles_black);
    this->ui->opponentManaValue->setToolTip("Mana");
    this->ui->opponentManaValue->raise();
    this->ui->opponentManaValue->setGeometry(this->ui->manaOpponent->geometry());
    this->ui->opponentManaValue->resize(51,42);
    this->ui->opponentManaValue->setStyleSheet(styles_black);
    this->ui->opponentHandCount->setToolTip("Cards in hand");
    this->ui->opponentHandCount->raise();
    this->ui->opponentHandCount->setGeometry(this->ui->handOpponent->geometry());
    this->ui->opponentHandCount->resize(51,42);
    this->ui->opponentHandCount->setStyleSheet(styles_white);
    this->ui->opponentDeckCount->setToolTip("Cards in deck");
    this->ui->opponentDeckCount->raise();
    this->ui->opponentDeckCount->setGeometry(this->ui->deckOpponent->geometry());
    this->ui->opponentDeckCount->resize(51,42);
    this->ui->opponentDeckCount->setStyleSheet(styles_white);
    this->ui->opponentSpecialDeckCount->setToolTip("Cards in sp. deck");
    this->ui->opponentSpecialDeckCount->raise();
    this->ui->opponentSpecialDeckCount->setGeometry(this->ui->specialDeckOpponent->geometry());
    this->ui->opponentSpecialDeckCount->resize(51,42);
    this->ui->opponentSpecialDeckCount->setStyleSheet(styles_white);
    this->ui->opponentSummonLimitValue->setToolTip("Remaining normal summons");
    this->ui->opponentSummonLimitValue->raise();
    this->ui->opponentSummonLimitValue->setGeometry(this->ui->summonLimitOpponent->geometry());
    this->ui->opponentSummonLimitValue->resize(51,42);
    this->ui->opponentSummonLimitValue->setStyleSheet(styles_black);
    this->botThinking(false);
    this->ui->spinningCircle->setMovie(circle);
    circle->start();
    this->ui->spinningCircle->setScaledContents(true);
    connect(this->ui->startDuelButton, &QPushButton::released, this, &MainWindow::startDuel);
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::startDuel()
{
    int playerDeck = this->ui->playerDeckSelectTraining->currentIndex()+1;
    int opponentDeck = this->ui->opponentDeckSelectTraining->currentIndex()+1;
    bot.setDifficulty(this->ui->difficultySlider->value());
    this->ui->targetBox->setVisible(false);
    this->ui->endDuelButton->setVisible(false);
    this->ui->endDuelButton->setDisabled(true);
    this->bridge = new DuelUiBridge;
    this->duel = new Duel;
    this->bridge->setDecks(playerDeck,opponentDeck);
    this->duel->getPlayer(1)->setBot(&bot);
    this->bridge->setDuel(duel);
    this->duel->setUiBridge(this->bridge);
    this->mutex = new QSemaphore(1);
    this->bridge->setMutex(this->mutex);
    connect(this->bridge,&DuelUiBridge::drawHand, this, &MainWindow::setHandImages);
    connect(this->bridge,&DuelUiBridge::drawGraveyard, this, &MainWindow::setGraveyardImages);
    connect(this->bridge,&DuelUiBridge::drawOpponentGraveyard, this, &MainWindow::setOpponentGraveyardImages);
    connect(this->bridge,&DuelUiBridge::drawSpecialDeck, this, &MainWindow::setSpecialDeckImages);
    connect(this->bridge,&DuelUiBridge::drawField, this, &MainWindow::setFieldImagesAndLabels);
    connect(this->bridge,&DuelUiBridge::drawResources, this, &MainWindow::setResources);
    connect(this->bridge,&DuelUiBridge::drawSpellTargets, this, &MainWindow::setSpellTargetImages);
    connect(this->bridge,&DuelUiBridge::drawFirstMaterialTargets, this, &MainWindow::setFirstMaterialTargetImages);
    connect(this->bridge,&DuelUiBridge::drawSecondMaterialTargets, this, &MainWindow::setSecondMaterialTargetImages);
    connect(this->bridge,&DuelUiBridge::drawLastMaterialTargets, this, &MainWindow::setLastMaterialTargetImages);
    connect(this->bridge,&DuelUiBridge::drawAttackers, this, &MainWindow::setAttackerTargetImages);
    connect(this->bridge,&DuelUiBridge::drawDefenders, this, &MainWindow::setDefenderTargetImages);
    connect(this->bridge,&DuelUiBridge::drawLogs, this, &MainWindow::setLogLabels);
    connect(this->ui->cardTabs, &QTabWidget::currentChanged, this, &MainWindow::clearTabs);
    connect(this, &MainWindow::duelStartSignal, this->bridge, &DuelUiBridge::initiateDuel);
    connect(this->ui->playFromHandButton, &QPushButton::released, this, &MainWindow::playFromHand);
    connect(this->ui->playSpecialMinionButton, &QPushButton::released, this, &MainWindow::playSpecialMinion);
    connect(this->ui->battlePhaseButton, &QPushButton::released, this, &MainWindow::startBattlePhase);
    connect(this, &MainWindow::handAction, this->bridge, &DuelUiBridge::playFromHand);
    connect(this, &MainWindow::specialDeckAction, this->bridge, &DuelUiBridge::playSpecialMinion);
    connect(this, &MainWindow::turnEndSignal, this->bridge, &DuelUiBridge::passTurn);
    connect(this, &MainWindow::startBattlePhaseSignal, this->bridge, &DuelUiBridge::battlePhase);
    connect(this->bridge,&DuelUiBridge::handCardPlayed,this, &MainWindow::handTarget);
    connect(this->bridge,&DuelUiBridge::specialMinionPlayed,this, &MainWindow::specialDeckTarget);
    connect(this->bridge,&DuelUiBridge::duelEndSignal, this, &MainWindow::endDuel);
    connect(this->bridge, &DuelUiBridge::drawTurnPlayer, this, &MainWindow::turnPlayer);
    connect(this->ui->endTurnButton, &QPushButton::released, this, &MainWindow::turnEnd);
    connect(this->ui->endDuelButton, &QPushButton::released, this, &MainWindow::clearDuel);
    connect(this->bridge, &DuelUiBridge::botThinkingSignal, this, &MainWindow::botThinking);

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
    this->logLabels = new QLabel* [0];
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
    Card* c;
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
        c = player->getHand()->at(i);
        std::string img = c->getCardName()->getImage();
        QString imgName = QString::fromStdString(std::string(":/")+img);
        QPixmap pm(imgName);
        handImages[i] = new CardLabel;
        handImages[i]->setParent(this->ui->handCardsAreaContents);
        handImages[i]->setMainWindowUi(this->ui);
        handImages[i]->setCard(c);
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
    ui->handCardsAreaContents->setGeometry(40,40,(i*80)+15,95);
    this->handSize = n_hand;
}
void MainWindow::setSpecialDeckImages()
{
    Card* c;
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
        c = player->getSpecialDeck()->at(i);
        std::string img = c->getCardName()->getImage();
        QString imgName = QString::fromStdString(std::string(":/")+img);
        QPixmap pm(imgName);
        specialDeckImages[i] = new CardLabel;
        specialDeckImages[i]->setParent(this->ui->specialDeckCardsAreaContents);
        specialDeckImages[i]->setMainWindowUi(this->ui);
        specialDeckImages[i]->setCard(c);
        specialDeckImages[i]->setPlace(4);
        specialDeckImages[i]->setId(i);
        specialDeckImages[i]->setHasImage(true);
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
    ui->specialDeckCardsAreaContents->setGeometry(40,40,(i*80)+15,95);
    this->specialDeckSize = n_special;
}
void MainWindow::setGraveyardImages()
{
    Card* c;
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
        c = player->getGraveyard()->at(i);
        std::string img = c->getCardName()->getImage();
        QString imgName = QString::fromStdString(std::string(":/") + img);
        QPixmap pm(imgName);
        graveyardImages[i] = new CardLabel;
        graveyardImages[i]->setParent(this->ui->graveyardCardsAreaContents);
        graveyardImages[i]->setMainWindowUi(this->ui);
        graveyardImages[i]->setCard(c);
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
    ui->graveyardCardsAreaContents->setGeometry(40,40,(i*80)+15,95);
    this->graveyardSize = n_graveyard;
}
void MainWindow::setOpponentGraveyardImages()
{
    Player* opponent = duel->getPlayer(1);
    Card* c;
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
        c = opponent->getGraveyard()->at(i);
        std::string img = c->getCardName()->getImage();
        QString imgName = QString::fromStdString(std::string(":/")+img);
        QPixmap pm(imgName);
        opponentGraveyardImages[i] = new CardLabel;
        opponentGraveyardImages[i]->setParent(this->ui->opponentGraveyardCardsAreaContents);
        opponentGraveyardImages[i]->setMainWindowUi(this->ui);
        opponentGraveyardImages[i]->setCard(c);
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
    ui->opponentGraveyardCardsAreaContents->setGeometry(40,40,(i*80)+15,95);
    this->opponentGraveyardSize = n_graveyard;
}
void MainWindow::handTarget(short id)
{
    if (!this->buttonBlock)
    {
    this->selectedHandCard = id;

    //short handSize = this->duel->getPlayer(0)->getHandSize();
        for (int i=0;i<this->handSize;i++)
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
    if (!this->buttonBlock)
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
void MainWindow::maintainHandTargetHighlight()
{
    if (this->selectedHandCard!=-1)
    {
    this->handImages[this->selectedHandCard]->setStyleSheet("border: 3px solid red;");
    }
}
void MainWindow::maintainSpecialDeckTargetHighlight()
{
    if (this->selectedSpecialDeckCard!=-1)
    {
    this->specialDeckImages[this->selectedSpecialDeckCard]->setStyleSheet("border: 3px solid red;");
    }
}
void MainWindow::spellTargetingTarget(int id)
{
    if (this->buttonBlock)
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
void MainWindow::attackerTargetingTarget(short id)
{
    if (this->buttonBlock)
    {
    this->selectedAttackerTarget = id;
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
void MainWindow::defenderTargetingTarget(short id)
{
    if (this->buttonBlock)
    {
    this->selectedDefenderTarget = id;
        for (int i=0;i<this->n_targets;i++)
        {
            this->targetImages[i]->setStyleSheet("border:none;");
        }
        if (id!=-1)
        {
            if (id==-10){this->targetImages[0]->setStyleSheet("border: 3px solid red;");}
            else{this->targetImages[id]->setStyleSheet("border: 3px solid red;");}
        }
    }
}
void MainWindow::materialTargetingTarget(short id)
{
    if (this->buttonBlock)
    {
    this->selectedMaterialTarget = id;
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
    if (this->selectedHandCard!=-1&&!this->buttonBlock)
    {
        emit handAction(this->selectedHandCard);
    }
}
void MainWindow::playSpecialMinion()
{
    if (this->selectedSpecialDeckCard!=-1&&!this->buttonBlock)
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
        playerFieldLabels[i]->setAlignment(Qt::AlignCenter);
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
        opponentFieldLabels[4-i]->setAlignment(Qt::AlignCenter);
        opponentFieldLabels[4-i]->setMouseTracking(true);
        opponentFieldLabels[4-i]->setFrameShape(QFrame::Box);
        opponentFieldLabels[4-i]->setVisible(true);
        opponentFieldLabels[4-i]->setGeometry((i*120)+15,15,120,20);
        opponentFieldLabels[4-i]->setContentsMargins(0,0,0,0);

        if (cardPlayer!=nullptr)
        {
            std::string img = cardPlayer->getCardName()->getImage();
            QString imgName = QString::fromStdString(std::string(":/")+img);
            QPixmap pm(imgName);
            playerFieldImages[i]->setCard(cardPlayer);
            playerFieldImages[i]->setId(i);
            playerFieldImages[i]->setPixmap(pm);
            playerFieldImages[i]->setHasImage(true);

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
            std::string img = cardOpp->getCardName()->getImage();
            QString imgName = QString::fromStdString(std::string(":/")+img);
            QPixmap pm(imgName);
            opponentFieldImages[4-i]->setCard(cardOpp);
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
            //qDebug()<<negated;
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

    ui->playerResources->setTabText(0, QString::fromStdString(player->getName()));
    ui->playerLifeValue->setText(QString::number(player->getHp()));
    ui->playerManaValue->setText(QString::number(player->getMana()));
    ui->playerDeckCount->setText(QString::number(player->getDeckSize()));
    ui->playerSummonLimitValue->setText(QString::number(player->getSummonLimit()));

    ui->opponentResources->setTabText(0, QString::fromStdString(opponent->getName()));
    ui->opponentLifeValue->setText(QString::number(opponent->getHp()));
    ui->opponentManaValue->setText(QString::number(opponent->getMana()));
    ui->opponentDeckCount->setText(QString::number(opponent->getDeckSize()));
    ui->opponentSpecialDeckCount->setText(QString::number(opponent->getSpecialDeckSize()));
    ui->opponentHandCount->setText(QString::number(opponent->getHandSize()));
    ui->opponentSummonLimitValue->setText(QString::number(opponent->getSummonLimit()));
}
void MainWindow::setSpellTargetImages(Card* card)
{
    std::vector<Card*>* targets = card->getCardName()->getTargetList()->getTargetList();
    short nt = card->getCardName()->getTargetList()->getTargetsNumber();
    Card* c;
    int i;
    this->buttonBlock = true;
    this->ui->targetBox->setVisible(true);
    this->ui->targetBox->setTabText(0, "Select target");
    connect(this->ui->confirmTargetButton, &QPushButton::released, this, &MainWindow::spellConfirm);
    connect(this->ui->cancelTargetButton, &QPushButton::released, this, &MainWindow::spellCancel);
    this->ui->confirmTargetButton->setText("Confirm");
    this->ui->cancelTargetButton->setText("Cancel");
    for (i=0;i<this->n_targets;i++)
    {
        delete this->targetImages[i];
    }
    delete [] this->targetImages;
    this->targetImages = new CardLabel* [nt];
    for (i=0;i<nt;i++)
    {
        c = targets->at(i);
        std::string img = c->getCardName()->getImage();
        QString imgName = QString::fromStdString(std::string(":/")+img);
        QPixmap pm(imgName);
        this->targetImages[i] = new CardLabel;
        this->targetImages[i]->setParent(this->ui->targetsAreaContents);
        this->targetImages[i]->setMainWindowUi(this->ui);
        this->targetImages[i]->setCard(c);
        this->targetImages[i]->setPlace(5);
        this->targetImages[i]->setId(i);
        this->targetImages[i]->setHasImage(true);
        this->targetImages[i]->setStyleSheet("border:none;");
        this->targetImages[i]->setPixmap(pm);
        this->targetImages[i]->setScaledContents(true);
        this->targetImages[i]->setMouseTracking(true);
        this->targetImages[i]->setFrameShape(QFrame::Box);
        this->targetImages[i]->setVisible(true);
        this->targetImages[i]->setGeometry((i*80)+15,15,80,80);
        this->targetImages[i]->setContentsMargins(0,0,0,0);

        connect(targetImages[i],&CardLabel::targetCardHighlight, this, &MainWindow::spellTargetingTarget);

    }
    this->ui->targetsAreaContents->setGeometry(40,40,(i*80)+15,95);
    this->n_targets = nt;
}
void MainWindow::setAttackerTargetImages()
{
    std::vector<Card*>* targets = this->duel->getAttackersList()->getTargetList();
    short nt = this->duel->getAttackersList()->getTargetsNumber();
    Card* c;
    int i;
    this->buttonBlock = true;
    this->ui->targetBox->setVisible(true);
    this->ui->targetBox->setTabText(0, "Select attacker");
    connect(this->ui->confirmTargetButton, &QPushButton::released, this, &MainWindow::attackerConfirm);
    connect(this->ui->cancelTargetButton, &QPushButton::released, this, &MainWindow::attackerCancel);

    if (!battled){this->ui->cancelTargetButton->setText("Cancel");}
    else {this->ui->cancelTargetButton->setText("End turn");}

    for (i=0;i<this->n_targets;i++)
    {
        delete this->targetImages[i];
    }
    delete [] this->targetImages;
    this->targetImages = new CardLabel* [nt];
    for (i=0;i<nt;i++)
    {
        c = targets->at(i);
        std::string img = c->getCardName()->getImage();
        QString imgName = QString::fromStdString(std::string(":/")+img);
        QPixmap pm(imgName);
        this->targetImages[i] = new CardLabel;
        this->targetImages[i]->setParent(this->ui->targetsAreaContents);
        this->targetImages[i]->setMainWindowUi(this->ui);
        this->targetImages[i]->setCard(c);
        this->targetImages[i]->setPlace(5);
        this->targetImages[i]->setId(i);
        this->targetImages[i]->setHasImage(true);
        this->targetImages[i]->setStyleSheet("border:none;");
        this->targetImages[i]->setPixmap(pm);
        this->targetImages[i]->setScaledContents(true);
        this->targetImages[i]->setMouseTracking(true);
        this->targetImages[i]->setFrameShape(QFrame::Box);
        this->targetImages[i]->setVisible(true);
        this->targetImages[i]->setGeometry((i*80)+15,15,80,80);
        this->targetImages[i]->setContentsMargins(0,0,0,0);

        connect(targetImages[i],&CardLabel::targetCardHighlight, this, &MainWindow::attackerTargetingTarget);

    }
    this->ui->targetsAreaContents->setGeometry(40,40,(i*80)+15,95);
    this->n_targets = nt;
}
void MainWindow::setDefenderTargetImages()
{
    std::vector<Card*>* targets = this->duel->getDefendersList()->getTargetList();
    short nt = this->duel->getDefendersList()->getTargetsNumber();
    Card* c;
    int i;
    this->buttonBlock = true;
    this->ui->targetBox->setVisible(true);
    this->ui->targetBox->setTabText(0, "Select attack target");
    connect(this->ui->confirmTargetButton, &QPushButton::released, this, &MainWindow::defenderConfirm);
    connect(this->ui->cancelTargetButton, &QPushButton::released, this, &MainWindow::defenderCancel);

    this->ui->confirmTargetButton->setText("Attack");
    this->ui->cancelTargetButton->setText("Back");
    for (i=0;i<this->n_targets;i++)
    {
        delete this->targetImages[i];
    }
    delete [] this->targetImages;
    if (nt>0){this->targetImages = new CardLabel* [nt];}
    else {this->targetImages = new CardLabel* [1];}

    for (i=0;i<nt;i++)
    {
        c = targets->at(i);
        std::string img = c->getCardName()->getImage();
        QString imgName = QString::fromStdString(std::string(":/")+img);
        QPixmap pm(imgName);
        this->targetImages[i] = new CardLabel;
        this->targetImages[i]->setParent(this->ui->targetsAreaContents);
        this->targetImages[i]->setMainWindowUi(this->ui);
        this->targetImages[i]->setCard(c);
        this->targetImages[i]->setPlace(5);
        this->targetImages[i]->setId(i);
        this->targetImages[i]->setHasImage(true);
        this->targetImages[i]->setStyleSheet("border:none;");
        this->targetImages[i]->setPixmap(pm);
        this->targetImages[i]->setScaledContents(true);
        this->targetImages[i]->setMouseTracking(true);
        this->targetImages[i]->setFrameShape(QFrame::Box);
        this->targetImages[i]->setVisible(true);
        this->targetImages[i]->setGeometry((i*80)+15,15,80,80);
        this->targetImages[i]->setContentsMargins(0,0,0,0);

        connect(targetImages[i],&CardLabel::targetCardHighlight, this, &MainWindow::defenderTargetingTarget);

    }
    if (nt==0)
    {
        this->targetImages[0] = new CardLabel;
        this->targetImages[0]->setParent(this->ui->targetsAreaContents);
        this->targetImages[0]->setMainWindowUi(this->ui);
        this->targetImages[0]->setPlace(5);
        this->targetImages[0]->setText("Direct\nAttack");
        this->targetImages[0]->setAlignment(Qt::AlignCenter);
        this->targetImages[0]->setId(-10);
        QFont f = this->targetImages[0]->font();
        f.setPointSize(18);
        this->targetImages[0]->setFont(f);
        this->targetImages[0]->setStyleSheet("border:none;");
        this->targetImages[0]->setScaledContents(true);
        this->targetImages[0]->setMouseTracking(true);
        this->targetImages[0]->setFrameShape(QFrame::Box);
        this->targetImages[0]->setVisible(true);
        this->targetImages[0]->setGeometry((i*80)+15,15,80,80);
        this->targetImages[0]->setContentsMargins(0,0,0,0);
        i = 1;
        connect(targetImages[0],&CardLabel::targetCardHighlight, this, &MainWindow::defenderTargetingTarget);
    }
    this->n_targets = nt;
    this->ui->targetsAreaContents->setGeometry(40,40,(i*80)+15,95);
    if (nt == 0){this->n_targets = 1;}
}

void MainWindow::setMaterialTargetImages(Card* card)
{
    std::vector<Card*>* targets = card->getCardName()->getTargetList()->getTargetList();
    short nt = card->getCardName()->getTargetList()->getTargetsNumber();
    Card* c;
    int i;
    for (i=0;i<this->n_targets;i++)
    {
        delete this->targetImages[i];
    }
    delete [] this->targetImages;
    this->targetImages = new CardLabel* [nt];
    for (i=0;i<nt;i++)
    {
        c = targets->at(i);
        std::string img = c->getCardName()->getImage();
        QString imgName = QString::fromStdString(std::string(":/")+img);
        QPixmap pm(imgName);
        this->targetImages[i] = new CardLabel;
        this->targetImages[i]->setParent(this->ui->targetsAreaContents);
        this->targetImages[i]->setMainWindowUi(this->ui);
        this->targetImages[i]->setCard(c);
        this->targetImages[i]->setPlace(5);
        this->targetImages[i]->setId(i);
        this->targetImages[i]->setHasImage(true);
        this->targetImages[i]->setStyleSheet("border:none;");
        this->targetImages[i]->setPixmap(pm);
        this->targetImages[i]->setScaledContents(true);
        this->targetImages[i]->setMouseTracking(true);
        this->targetImages[i]->setFrameShape(QFrame::Box);
        this->targetImages[i]->setVisible(true);
        this->targetImages[i]->setGeometry((i*80)+15,15,80,80);
        this->targetImages[i]->setContentsMargins(0,0,0,0);

        connect(targetImages[i],&CardLabel::targetCardHighlight, this, &MainWindow::materialTargetingTarget);

    }
    this->ui->targetsAreaContents->setGeometry(40,40,(i*80)+15,95);
    this->n_targets = nt;
}
void MainWindow::setFirstMaterialTargetImages(Card* card)
{
    this->buttonBlock = true;
    this->ui->targetBox->setVisible(true);
    this->ui->targetBox->setTabText(0, "Select first material");
    connect(this->ui->confirmTargetButton, &QPushButton::released, this, &MainWindow::specialMinionConfirm);
    connect(this->ui->cancelTargetButton, &QPushButton::released, this, &MainWindow::specialMinionCancel);
    this->ui->confirmTargetButton->setText("Confirm");
    this->ui->cancelTargetButton->setText("Cancel");
    this->setMaterialTargetImages(card);
}
void MainWindow::setSecondMaterialTargetImages(Card* card)
{
    this->buttonBlock = true;
    this->ui->targetBox->setVisible(true);
    this->ui->targetBox->setTabText(0, "Select second material");
    connect(this->ui->confirmTargetButton, &QPushButton::released, this, &MainWindow::specialMinionConfirm);
    connect(this->ui->cancelTargetButton, &QPushButton::released, this, &MainWindow::specialMinionCancel);
    this->ui->confirmTargetButton->setText("Confirm");
    this->ui->cancelTargetButton->setText("Cancel");
    this->setMaterialTargetImages(card);
}
void MainWindow::setLastMaterialTargetImages(Card* card)
{
    this->buttonBlock = true;
    this->ui->targetBox->setVisible(true);
    this->ui->targetBox->setTabText(0, "Select last material");
    connect(this->ui->confirmTargetButton, &QPushButton::released, this, &MainWindow::specialMinionConfirm);
    connect(this->ui->cancelTargetButton, &QPushButton::released, this, &MainWindow::specialMinionCancel);
    this->ui->confirmTargetButton->setText("Confirm");
    this->ui->cancelTargetButton->setText("Cancel");
    this->setMaterialTargetImages(card);
}
void MainWindow::spellConfirm()
{
    if (this->selectedSpellTarget!=-1)
    {
        this->bridge->setSpellTarget(this->targetImages[this->selectedSpellTarget]->getCard()->getCopyId());
        this->buttonBlock = false;
        this->selectedSpellTarget = -1;
        disconnect(this->ui->cancelTargetButton, nullptr, nullptr, nullptr);
        disconnect(this->ui->confirmTargetButton, nullptr, nullptr, nullptr);
        this->clearTargets();
        if (this->mutex->available()==0) {mutex->release();}
    }
}
void MainWindow::spellCancel()
{
    this->bridge->setSpellTarget(-1);
    this->buttonBlock = false;
    this->selectedSpellTarget = -1;
    disconnect(this->ui->cancelTargetButton, nullptr, nullptr, nullptr);
    disconnect(this->ui->confirmTargetButton, nullptr, nullptr, nullptr);
    this->clearTargets();
    if (this->mutex->available()==0) {mutex->release();}
}
void MainWindow::specialMinionConfirm()
{
    if (this->selectedMaterialTarget!=-1)
    {
        this->bridge->setMaterialTarget(this->selectedMaterialTarget);
        this->buttonBlock = false;
        this->selectedMaterialTarget = -1;
        disconnect(this->ui->cancelTargetButton, nullptr, nullptr, nullptr);
        disconnect(this->ui->confirmTargetButton, nullptr, nullptr, nullptr);
        this->clearTargets();
        if (this->mutex->available()==0) {mutex->release();}
    }
}
void MainWindow::specialMinionCancel()
{
    this->bridge->setMaterialTarget(-1);
    this->bridge->setSelectedMaterials(0);
    this->buttonBlock = false;
    this->selectedMaterialTarget = -1;
    disconnect(this->ui->cancelTargetButton, nullptr, nullptr, nullptr);
    disconnect(this->ui->confirmTargetButton, nullptr, nullptr, nullptr);
    this->clearTargets();
    if (this->mutex->available()==0) {mutex->release();}
}
void MainWindow::attackerConfirm()
{
    if (this->selectedAttackerTarget!=-1)
    {
        this->bridge->setAttackerTarget(this->selectedAttackerTarget);
        this->selectedAttackerTarget = -1;
        disconnect(this->ui->cancelTargetButton, nullptr, nullptr, nullptr);
        disconnect(this->ui->confirmTargetButton, nullptr, nullptr, nullptr);
        this->clearTargets();
        if (this->mutex->available()==0) {mutex->release();}
    }
}
void MainWindow::attackerCancel()
{
    this->bridge->setAttackerTarget(-1);
    this->buttonBlock = false;
    this->selectedAttackerTarget = -1;
    disconnect(this->ui->cancelTargetButton, nullptr, nullptr, nullptr);
    disconnect(this->ui->confirmTargetButton, nullptr, nullptr, nullptr);
    this->clearTargets();
    if (this->mutex->available()==0) {mutex->release();}
    if (this->battled&&!this->duelEnd)
    {
        this->turnEnd();
    }
}
void MainWindow::defenderConfirm()
{
    if (this->selectedDefenderTarget!=-1)
    {
        this->bridge->setDefenderTarget(this->selectedDefenderTarget);
        this->selectedDefenderTarget = -1;
        disconnect(this->ui->cancelTargetButton, nullptr, nullptr, nullptr);
        disconnect(this->ui->confirmTargetButton, nullptr, nullptr, nullptr);
        this->battled = true;
        this->clearTargets();
        if (this->mutex->available()==0) {mutex->release();}
    }
}
void MainWindow::defenderCancel()
{
    this->bridge->setDefenderTarget(-1);
    this->selectedDefenderTarget = -1;
    disconnect(this->ui->cancelTargetButton, nullptr, nullptr, nullptr);
    disconnect(this->ui->confirmTargetButton, nullptr, nullptr, nullptr);
    clearTargets();
    if (this->mutex->available()==0) {mutex->release();}
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
    this->ui->targetBox->setVisible(false);
}
void MainWindow::clearTabs()
{
    this->setHandImages();
    this->maintainHandTargetHighlight();
    this->setSpecialDeckImages();
    this->maintainSpecialDeckTargetHighlight();
    this->setGraveyardImages();
    this->setOpponentGraveyardImages();
    if (!this->buttonBlock)
    {
        this->selectedHandCard = -1;
        this->selectedSpellTarget = -1;
        this->selectedSpecialDeckCard = -1;
        this->selectedMaterialTarget = -1;
    }

}
void MainWindow::turnEnd()
{
        if (this->duel->getTurnPlayer()==0&&!this->buttonBlock)
        {
            this->battled = false;
            emit turnEndSignal();
        }
}
void MainWindow::startBattlePhase()
{
    if (!this->buttonBlock&&duel->getTurnCount()>1)
    {
        emit startBattlePhaseSignal();
    }
}
void MainWindow::setLogLabels()
{

    int n_logs = this->duel->getLogsNumber();
    if (n_logs == this->drawnLogs) {return;}
    QLabel** logs_new = new QLabel* [n_logs];
    int i;
    for (i = 0;i<this->drawnLogs;i++)
    {
        logs_new[i] = this->logLabels[i];
    }
    for (i = this->drawnLogs;i<n_logs;i++)
    {
        logs_new[i] = new QLabel;
        std::string str = this->duel->getLogs()[i];

        logs_new[i]->setText(QString::fromStdString(str));
        logs_new[i]->setParent(this->ui->duelLogsAreaContents);
        logs_new[i]->setScaledContents(true);
        logs_new[i]->setWordWrap(true);
        logs_new[i]->setFrameShape(QFrame::Box);
        QString color;
        short source = this->duel->getLogSources()[i];
        if (source==0) {color = "#3366ff";}
        else if (source==1) {color = "#e14b3d";}
        else if (source==2) {color = "white";}
        logs_new[i]->setStyleSheet("border:none; border-left:4px solid "+ color + ";");
        logs_new[i]->setVisible(true);
        if (str.length()>66) {
            logs_new[i]->setGeometry(5,5+(i*28)+20*(this->longerLogs),425,40);
            this->longerLogs++;
        }
        else{
            logs_new[i]->setGeometry(5,5+(i*28)+20*(this->longerLogs),425,20);
        }

    }

    this->ui->duelLogsAreaContents->setGeometry(0,0,461, 5 + (n_logs * 28)+28*(this->longerLogs));
    this->ui->duelLogsArea->verticalScrollBar()->setValue(n_logs * 28 +20*(this->longerLogs));
    delete [] this->logLabels;
    this->logLabels = logs_new;
    this->drawnLogs = n_logs;
}
void MainWindow::endDuel(short result)
{
    if (result!=-1)
    {
        this->duelEnd = true;
        this->attackerCancel();
        this->defenderCancel();
        this->specialMinionCancel();
        this->spellCancel();
        this->buttonBlock = true;
        this->ui->endDuelButton->setVisible(true);
        this->ui->endDuelButton->setDisabled(false);
    }
}
void MainWindow::clearDuel()
{
    for (int i=0;i<this->handSize;i++)
    {
        delete this->handImages[i];
    }
    delete [] this->handImages;
    for (int i=0;i<this->graveyardSize;i++)
    {
        delete this->graveyardImages[i];
    }
    delete [] this->graveyardImages;
    for (int i=0;i<this->opponentGraveyardSize;i++)
    {
        delete this->opponentGraveyardImages[i];
    }
    delete [] this->opponentGraveyardImages;
    for (int i=0;i<this->specialDeckSize;i++)
    {
        delete this->specialDeckImages[i];
    }
    delete [] this->specialDeckImages;
    for (int i=0;i<5;i++)
    {
        delete this->playerFieldImages[i];
        delete this->playerFieldLabels[i];
        delete this->opponentFieldImages[i];
        delete this->opponentFieldLabels[i];
    }
    delete [] this->playerFieldImages;
    delete [] this->playerFieldLabels;
    delete [] this->opponentFieldImages;
    delete [] this->opponentFieldLabels;
    for (int i=0;i<this->drawnLogs;i++)
    {
        delete this->logLabels[i];
    }
    delete [] logLabels;
    this->drawnLogs = 0;
    this->longerLogs = 0;
    this->selectedHandCard = -1;
    this->selectedSpellTarget = -1;
    this->selectedMaterialTarget = -1;
    this->selectedSpecialDeckCard = -1;
    this->selectedAttackerTarget = -1;
    this->selectedDefenderTarget = -1;
    this-> handSize = 0;
    this-> specialDeckSize = 0;
    this->graveyardSize = 0;
    this->opponentGraveyardSize = 0;
    this->n_targets = 0;
    this->buttonBlock = false;
    this->battled = false;
    this->duelEnd = false;

    disconnect(this->bridge,&DuelUiBridge::drawHand, this, &MainWindow::setHandImages);
    disconnect(this->bridge,&DuelUiBridge::drawGraveyard, this, &MainWindow::setGraveyardImages);
    disconnect(this->bridge,&DuelUiBridge::drawOpponentGraveyard, this, &MainWindow::setOpponentGraveyardImages);
    disconnect(this->bridge,&DuelUiBridge::drawSpecialDeck, this, &MainWindow::setSpecialDeckImages);
    disconnect(this->bridge,&DuelUiBridge::drawField, this, &MainWindow::setFieldImagesAndLabels);
    disconnect(this->bridge,&DuelUiBridge::drawResources, this, &MainWindow::setResources);
    disconnect(this->bridge,&DuelUiBridge::drawSpellTargets, this, &MainWindow::setSpellTargetImages);
    disconnect(this->bridge,&DuelUiBridge::drawFirstMaterialTargets, this, &MainWindow::setFirstMaterialTargetImages);
    disconnect(this->bridge,&DuelUiBridge::drawSecondMaterialTargets, this, &MainWindow::setSecondMaterialTargetImages);
    disconnect(this->bridge,&DuelUiBridge::drawLastMaterialTargets, this, &MainWindow::setLastMaterialTargetImages);
    disconnect(this->bridge,&DuelUiBridge::drawAttackers, this, &MainWindow::setAttackerTargetImages);
    disconnect(this->bridge,&DuelUiBridge::drawDefenders, this, &MainWindow::setDefenderTargetImages);
    disconnect(this->bridge,&DuelUiBridge::drawLogs, this, &MainWindow::setLogLabels);
    disconnect(this->ui->cardTabs, &QTabWidget::currentChanged, this, &MainWindow::clearTabs);
    disconnect(this, &MainWindow::duelStartSignal, this->bridge, &DuelUiBridge::initiateDuel);
    disconnect(this->ui->playFromHandButton, &QPushButton::released, this, &MainWindow::playFromHand);
    disconnect(this->ui->playSpecialMinionButton, &QPushButton::released, this, &MainWindow::playSpecialMinion);
    disconnect(this->ui->battlePhaseButton, &QPushButton::released, this, &MainWindow::startBattlePhase);
    disconnect(this, &MainWindow::handAction, this->bridge, &DuelUiBridge::playFromHand);
    disconnect(this, &MainWindow::specialDeckAction, this->bridge, &DuelUiBridge::playSpecialMinion);
    disconnect(this, &MainWindow::turnEndSignal, this->bridge, &DuelUiBridge::passTurn);
    disconnect(this, &MainWindow::startBattlePhaseSignal, this->bridge, &DuelUiBridge::battlePhase);
    disconnect(this->bridge,&DuelUiBridge::handCardPlayed,this, &MainWindow::handTarget);
    disconnect(this->bridge,&DuelUiBridge::specialMinionPlayed,this, &MainWindow::specialDeckTarget);
    disconnect(this->bridge,&DuelUiBridge::duelEndSignal, this, &MainWindow::endDuel);
    disconnect(this->bridge, &DuelUiBridge::drawTurnPlayer, this, &MainWindow::turnPlayer);
    disconnect(this->ui->endTurnButton, &QPushButton::released, this, &MainWindow::turnEnd);
    disconnect(this->ui->endDuelButton, &QPushButton::released, this, &MainWindow::clearDuel);
    disconnect(this->bridge, &DuelUiBridge::botThinkingSignal, this, &MainWindow::botThinking);
    this->duelThread.exit();
    delete this->duel;
    delete this->bridge;
    this->ui->stackedWidget->setCurrentIndex(0);
}
void MainWindow::turnPlayer()
{
    short tc = this->duel->getTurnCount();
    short tp = this->duel->getTurnPlayer();
    std::string name = std::string(this->duel->getPlayer(this->duel->getTurnPlayer())->getName());
    std::string color;
    if (tp == 0) {color = "#3366ff";}
    if (tp == 1) {color = "#e14b3d";}
    std::string str = "Turn " + std::to_string(tc) +"<br/><span style=\"color:"+color+";\">[" + name + "]</span>";
    QString qstr = QString::fromStdString(str);
    this->ui->turnCountLabel->setText(qstr);
}
void MainWindow::botThinking(bool v)
{
    this->ui->spinningCircle->setVisible(v);
    this->ui->botThinking->setVisible(v);
}

void MainWindow::loadDecks()
{
    this->ui->playerDeckSelectTraining->setInsertPolicy(QComboBox::InsertAtBottom);
    this->ui->opponentDeckSelectTraining->setInsertPolicy(QComboBox::InsertAtBottom);

    this->ui->playerDeckSelectTraining->addItem("Starter Deck: Earth");
    this->ui->playerDeckSelectTraining->addItem("Starter Deck: Air");
    this->ui->playerDeckSelectTraining->addItem("Starter Deck: Wind-Up");

    this->ui->opponentDeckSelectTraining->addItem("Starter Deck: Earth");
    this->ui->opponentDeckSelectTraining->addItem("Starter Deck: Air");
    this->ui->opponentDeckSelectTraining->addItem("Starter Deck: Wind-Up");

}



