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
    bool image = false;
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
    bool hasImage() {return this->image;}
    void setHasImage(bool i) {this->image = i;}
signals:
    void handCardHighlight(short id);
    void targetCardHighlight(short id);
    void specialDeckCardHighlight(short id);
};

#endif // CARDLABEL_H
