#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QPixmap>
#include <QThread>
#include <QMutex>
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
    QMutex mutex;
    CardLabel** handImages;
    CardLabel** graveyardImages;
    CardLabel** opponentGraveyardImages;
    CardLabel** specialDeckImages;
    CardLabel** playerFieldImages;
    CardLabel** playerFieldLabels;
    CardLabel** opponentFieldImages;
    CardLabel** opponentFieldLabels;
    CardLabel** targetImages;
    short selectedHandCard = -1;
    short selectedSpellTarget = -1;
    short selectedMaterialTarget = -1;
    short selectedSpecialDeckCard = -1;
    short handSize = 0;
    short specialDeckSize = 0;
    short graveyardSize = 0;
    short opponentGraveyardSize = 0;
    short n_targets = 0;
    bool targeting = false;
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void startDuel();
    void clearTargets();
    void setMaterialTargetImages(Card* card);
    void maintainHandTargetHighlight();
    void maintainSpecialDeckTargetHighlight();
public slots:
    void setHandImages();
    void setSpecialDeckImages();
    void setGraveyardImages();
    void setOpponentGraveyardImages();
    void setFieldImagesAndLabels();
    void setResources();
    void handTarget(short id);
    void specialDeckTarget(short id);
    void spellTargetingTarget(short id);
    void materialTargetingTarget(short id);
    void playFromHand();
    void playSpecialMinion();
    void setSpellTargetImages(Card* card);
    void setFirstMaterialTargetImages(Card* card);
    void setSecondMaterialTargetImages(Card* card);
    void setLastMaterialTargetImages(Card* card);
    void spellConfirm();
    void spellCancel();
    void specialMinionConfirm();
    void specialMinionCancel();
    void clearTabs();
    void turnEnd();
signals:
    void duelStartSignal();
    void handAction(short id);
    void specialDeckAction(short id);
    void spellTarget(short id);
    void turnEndSignal();

};
#endif // MAINWINDOW_H
