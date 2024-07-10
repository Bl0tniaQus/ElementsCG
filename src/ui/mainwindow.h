#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QPixmap>
#include <QThread>
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
    DuelUiBridge bridge;
    QThread duelThread;
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
    short handSize = 0;
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void startDuel();
public slots:
    void setHandImages();
    void handTarget(short id);
    void playFromHand();
signals:
    void duelStartSignal();
    void handAction(short id);

};
#endif // MAINWINDOW_H
