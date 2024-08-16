#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QPixmap>
#include <QThread>
#include <QSemaphore>
#include <QMouseEvent>
#include "../engine/duel.h"
#include "dueluibridge.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    Ui::MainWindow *ui;
    Duel* duel;
    DuelUiBridge* bridge;
    QThread duelThread;
    QSemaphore* mutex;
    CardLabel** handImages;
    CardLabel** graveyardImages;
    CardLabel** opponentGraveyardImages;
    CardLabel** specialDeckImages;
    CardLabel** playerFieldImages;
    CardLabel** playerFieldLabels;
    CardLabel** opponentFieldImages;
    CardLabel** opponentFieldLabels;
    CardLabel** targetImages;
    QLabel** logLabels;
    int drawnLogs = 0;
    int longerLogs = 0;
    short selectedHandCard = -1;
    short selectedSpellTarget = -1;
    short selectedMaterialTarget = -1;
    short selectedSpecialDeckCard = -1;
    short selectedAttackerTarget = -1;
    short selectedDefenderTarget = -1;
    short handSize = 0;
    short specialDeckSize = 0;
    short graveyardSize = 0;
    short opponentGraveyardSize = 0;
    short n_targets = 0;
    bool buttonBlock = false;
    bool battled = false;
    bool duelEnd = false;
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void mouseMoveEvent(QMouseEvent* mouseEvent) override {mouseEvent->ignore();};
    void mouseReleaseEvent(QMouseEvent* mouseEvent) override {mouseEvent->ignore();};
    void mousePressEvent(QMouseEvent* mouseEvent) override {mouseEvent->ignore();};
    void moveEvent (QMoveEvent* mouseEvent) override {mouseEvent->ignore();};
    void startDuel();
    void clearTargets();
    void setMaterialTargetImages(Card* card);
    void maintainHandTargetHighlight();
    void maintainSpecialDeckTargetHighlight();
    void clearDuel();
    void loadDecks();
public slots:
    void setHandImages();
    void setSpecialDeckImages();
    void setGraveyardImages();
    void setOpponentGraveyardImages();
    void setFieldImagesAndLabels();
    void setResources();
    void setAttackerTargetImages();
    void setDefenderTargetImages();
    void setLogLabels();
    void handTarget(short id);
    void specialDeckTarget(short id);
    void spellTargetingTarget(short id);
    void materialTargetingTarget(short id);
    void attackerTargetingTarget(short id);
    void defenderTargetingTarget(short id);
    void playFromHand();
    void startBattlePhase();
    void playSpecialMinion();
    void setSpellTargetImages(Card* card);
    void setFirstMaterialTargetImages(Card* card);
    void setSecondMaterialTargetImages(Card* card);
    void setLastMaterialTargetImages(Card* card);
    void spellConfirm();
    void spellCancel();
    void specialMinionConfirm();
    void specialMinionCancel();
    void attackerConfirm();
    void attackerCancel();
    void defenderConfirm();
    void defenderCancel();
    void clearTabs();
    void turnEnd();
    void endDuel(short result);
signals:
    void duelStartSignal();
    void handAction(short id);
    void specialDeckAction(short id);
    void startBattlePhaseSignal();
    void spellTarget(short id);
    void turnEndSignal();

};
#endif // MAINWINDOW_H
