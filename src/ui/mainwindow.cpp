#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "../engine/globals.h"
#include "../engine/card.h"
#include "../engine/zone.h"
#include <iostream>
#include <QDebug>
#include <QScrollBar>
MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow), duelThread(this)
{
    this->ui->setupUi(this);
    this->setFixedSize(1600,900);
    this->ui->stackedWidget->setCurrentIndex(0);
    delete this->ui->uselessTabTarget;
    delete this->ui->playerNameUselessTab;
    delete this->ui->opponentNameUselessTab;
    delete this->ui->duelLogUselessTab;
    connect(this->ui->testButton, &QPushButton::released, this, &MainWindow::startDuel);
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::startDuel()
{
    this->ui->targetBox->setVisible(false);
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
        c = player->getHand()[i];
        char* img = c->getCardName()->getImage();
        QString imgName = QString::fromStdString(std::string(":/")+std::string(img));
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
        c = player->getSpecialDeck()[i];
        char* img = c->getCardName()->getImage();
        QString imgName = QString::fromStdString(std::string(":/")+std::string(img));
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
        c = player->getGraveyard()[i];
        char* img = c->getCardName()->getImage();
        QString imgName = QString::fromStdString(std::string(":/")+std::string(img));
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
        c = opponent->getGraveyard()[i];
        char* img = c->getCardName()->getImage();
        QString imgName = QString::fromStdString(std::string(":/")+std::string(img));
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
void MainWindow::spellTargetingTarget(short id)
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
void MainWindow::attackerTargetingTarget(short id)
{
    if (targeting)
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
    if (targeting)
    {
    this->selectedDefenderTarget = id;
        for (int i=0;i<this->n_targets;i++)
        {
            this->targetImages[i]->setStyleSheet("border:none;");
        }
        if (id!=-1)
        {
            if (id==10){this->targetImages[0]->setStyleSheet("border: 3px solid red;");}
            else{this->targetImages[id]->setStyleSheet("border: 3px solid red;");}
        }
    }
}
void MainWindow::materialTargetingTarget(short id)
{
    if (targeting)
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
            char* img = cardPlayer->getCardName()->getImage();
            QString imgName = QString::fromStdString(std::string(":/")+std::string(img));
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
            char* img = cardOpp->getCardName()->getImage();
            QString imgName = QString::fromStdString(std::string(":/")+std::string(img));
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

    ui->playerResources->setTabText(0, QString(player->getName()));
    ui->playerLifeValue->setText(QString::number(player->getHp()));
    ui->playerManaValue->setText(QString::number(player->getMana()));
    ui->playerDeckCount->setText(QString::number(player->getDeckSize()));
    ui->playerSummonLimitValue->setText(QString::number(player->getSummonLimit()));

    ui->opponentResources->setTabText(0, QString(opponent->getName()));
    ui->opponentLifeValue->setText(QString::number(opponent->getHp()));
    ui->opponentManaValue->setText(QString::number(opponent->getMana()));
    ui->opponentDeckCount->setText(QString::number(opponent->getDeckSize()));
    ui->opponentSpecialDeckCount->setText(QString::number(opponent->getSpecialDeckSize()));
    ui->opponentHandCount->setText(QString::number(opponent->getHandSize()));
    ui->opponentSummonLimitValue->setText(QString::number(opponent->getSummonLimit()));
}
void MainWindow::setSpellTargetImages(Card* card)
{
    Card** targets = card->getCardName()->getTargetList()->getTargetList();
    short nt = card->getCardName()->getTargetList()->getTargetsNumber();
    Card* c;
    int i;
    this->targeting = true;
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
        c = targets[i];
        char* img = c->getCardName()->getImage();
        QString imgName = QString::fromStdString(std::string(":/")+std::string(img));
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
    Card** targets = this->duel->getAttackersList()->getTargetList();
    short nt = this->duel->getAttackersList()->getTargetsNumber();
    Card* c;
    int i;
    this->targeting = true;
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
        c = targets[i];
        char* img = c->getCardName()->getImage();
        QString imgName = QString::fromStdString(std::string(":/")+std::string(img));
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
    Card** targets = this->duel->getDefendersList()->getTargetList();
    short nt = this->duel->getDefendersList()->getTargetsNumber();
    Card* c;
    int i;
    this->targeting = true;
    this->ui->targetBox->setVisible(true);
    this->ui->targetBox->setTabText(0, "Select attack target");
    connect(this->ui->confirmTargetButton, &QPushButton::released, this, &MainWindow::defenderConfirm);
    connect(this->ui->cancelTargetButton, &QPushButton::released, this, &MainWindow::defenderCancel);

    this->ui->cancelTargetButton->setText("Back");
    this->ui->confirmTargetButton->setText("Attack");
    for (i=0;i<this->n_targets;i++)
    {
        delete this->targetImages[i];
    }
    delete [] this->targetImages;
    if (nt>0){this->targetImages = new CardLabel* [nt];}
    else {this->targetImages = new CardLabel* [1];}

    for (i=0;i<nt;i++)
    {
        c = targets[i];
        char* img = c->getCardName()->getImage();
        QString imgName = QString::fromStdString(std::string(":/")+std::string(img));
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
        this->targetImages[0]->setId(10);
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
    Card** targets = card->getCardName()->getTargetList()->getTargetList();
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
        c = targets[i];
        char* img = c->getCardName()->getImage();
        QString imgName = QString::fromStdString(std::string(":/")+std::string(img));
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
    this->targeting = true;
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
    this->targeting = true;
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
    this->targeting = true;
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
void MainWindow::specialMinionConfirm()
{
    if (this->selectedMaterialTarget!=-1)
    {
        this->bridge->setMaterialTarget(this->selectedMaterialTarget);
        if (this->bridge->getSelectedMaterials()==1) {this->targeting = false;}
        this->selectedMaterialTarget = -1;
        disconnect(this->ui->cancelTargetButton, nullptr, nullptr, nullptr);
        disconnect(this->ui->confirmTargetButton, nullptr, nullptr, nullptr);
        clearTargets();
        mutex.unlock();
    }
}
void MainWindow::specialMinionCancel()
{
    this->bridge->setMaterialTarget(-1);
    this->bridge->setSelectedMaterials(0);
    this->targeting = false;
    this->selectedMaterialTarget = -1;
    disconnect(this->ui->cancelTargetButton, nullptr, nullptr, nullptr);
    disconnect(this->ui->confirmTargetButton, nullptr, nullptr, nullptr);
    clearTargets();
    mutex.unlock();
}
void MainWindow::attackerConfirm()
{
    if (this->selectedAttackerTarget!=-1)
    {
        this->bridge->setAttackerTarget(this->selectedAttackerTarget);
        this->selectedAttackerTarget = -1;
        disconnect(this->ui->cancelTargetButton, nullptr, nullptr, nullptr);
        disconnect(this->ui->confirmTargetButton, nullptr, nullptr, nullptr);
        clearTargets();
        mutex.unlock();
    }
}
void MainWindow::attackerCancel()
{
    this->bridge->setAttackerTarget(-1);
    this->targeting = false;
    this->selectedAttackerTarget = -1;
    disconnect(this->ui->cancelTargetButton, nullptr, nullptr, nullptr);
    disconnect(this->ui->confirmTargetButton, nullptr, nullptr, nullptr);
    clearTargets();
    mutex.unlock();
    if (battled)
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
        clearTargets();
        mutex.unlock();
    }
}
void MainWindow::defenderCancel()
{
    this->bridge->setDefenderTarget(-1);
    this->selectedDefenderTarget = -1;
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
    if (!targeting)
    {
        this->selectedHandCard = -1;
        this->selectedSpellTarget = -1;
        this->selectedSpecialDeckCard = -1;
        this->selectedMaterialTarget = -1;
    }

}
void MainWindow::turnEnd()
{
        if (this->duel->getTurnPlayer()==0&&!targeting)
        {
            this->battled = false;
            emit turnEndSignal();
        }
}
void MainWindow::startBattlePhase()
{
    if (!targeting&&duel->getTurnCount()>1)
    {
        emit startBattlePhaseSignal();
    }
}
void MainWindow::setLogLabels()
{

    int n_logs = this->duel->getLogsNumber();

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
        logs_new[i]->setFrameShape(QFrame::Box);
        QString color;
        short source = this->duel->getLogSources()[i];
        if (source==0) {color = "blue";}
        else if (source==1) {color = "red";}
        else if (source==2) {color = "white";}
        logs_new[i]->setStyleSheet("border:none; border-left:4px solid "+ color + ";");
        logs_new[i]->setVisible(true);
        logs_new[i]->setGeometry(5,5+(i*28),425,20);
    }
    this->ui->duelLogsAreaContents->setGeometry(0,0,461, 5+ (n_logs * 28));
    this->ui->duelLogsArea->verticalScrollBar()->setValue(n_logs * 28);
    delete [] this->logLabels;
    this->logLabels = logs_new;
    this->drawnLogs = n_logs;

}

