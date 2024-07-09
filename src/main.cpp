#include "engine/duel.h"
#include "engine/globals.h"
#include "ui/mainwindow.h"
#include <iostream>
#include <QApplication>

int main(int argc, char *argv[])
{
    srand(time(NULL));
    QApplication a(argc, argv);
    MainWindow w;
    Duel duel;
    Deck deck(1);
    Deck deck2(2);

    duel.getPlayer(1)->setBot(&bot);
    duel.DuelControl(&deck,&deck2);
    //w.show();
   // return a.exec();
   //todo gui, duel threading, ui
    //field ui, play from hand

}
