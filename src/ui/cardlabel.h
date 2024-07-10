#pragma once

#ifndef CARDLABEL_H
#define CARDLABEL_H
#include <QLabel>
#include "ui_mainwindow.h"
class CardLabel : public QLabel
{
    Q_OBJECT
private:
    char* cardName;
    Ui::MainWindow* ui;
    short id;
public:
    ~CardLabel();
    void mouseMoveEvent(QMouseEvent* mouseEvent) override;
    void mouseReleaseEvent(QMouseEvent* mouseEvent) override;
    void setMainWindowUi(Ui::MainWindow* ui) {this->ui = ui;}
    void setCard(const char* c);
    void setId(short i) {this->id = i;}
    short getId() {return this->id;}
signals:
    void handCardHighlight(short id);
};

#endif // CARDLABEL_H
