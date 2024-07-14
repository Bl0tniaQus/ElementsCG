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
    short place; //0 - deck, 1 - hand, 2 - field, 3 - GY, 4 - special deck, 5 - target
public:
    ~CardLabel();
    CardLabel();
    void mouseMoveEvent(QMouseEvent* mouseEvent) override;
    void mouseReleaseEvent(QMouseEvent* mouseEvent) override;
    void setMainWindowUi(Ui::MainWindow* ui) {this->ui = ui;}
    void setCard(const char* c);
    void setId(short i) {this->id = i;}
    void setPlace(short place) {this->place = place;}
    short getPlace() {return this->place;}
    short getId() {return this->id;}
signals:
    void handCardHighlight(short id);
    void targetCardHighlight(short id);
};

#endif // CARDLABEL_H
