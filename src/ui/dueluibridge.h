#ifndef DUELUIBRIDGE_H
#define DUELUIBRIDGE_H
#include "mainwindow.h"
class Duel;
class DuelUiBridge
{
private:
    Duel* duel;
    Ui::MainWindow* ui;
public:
    DuelUiBridge();
    DuelUiBridge(Duel* duel, Ui::MainWindow* ui);
    void setHandImages();
};

#endif
