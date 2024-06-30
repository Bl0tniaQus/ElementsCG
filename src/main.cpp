#include "mainwindow.h"
#include "zone.h"
#include "player.h"
#include "card.h"
#include "duel.h"
#include "time.h"
#include "targetlist.h"
#include <iostream>
#include <QApplication>

int main(int argc, char *argv[])
{
    srand(time(NULL));
    //QApplication a(argc, argv);
    //MainWindow w;
    //w.show();
    //return a.exec();
    Duel duel;
    Deck deck(1);
    Deck deck2(2);
    duel.getPlayer(1)->setBot();
    duel.DuelControl(&deck,&deck2);
    //todo
    //remake cards for new system
    //end of turn effects remake
    //cards with new mechanics(search, barrier, stat modify, destruction, multiple attacks, search, GY interaction)
    //bot
    //gui

}
