#include "engine/duel.h"
#include "engine/globals.h"
#include "ui/mainwindow.h"
#include <iostream>
#include <QApplication>
#include <QDebug>
int main(int argc, char *argv[])
{
    srand(time(NULL));
    QApplication a(argc, argv);
    MainWindow w;
   // Duel duel;
   // Deck deck(1);
   // Deck deck2(2);

    //duel.getPlayer(1)->setBot(&bot);
    //duel.DuelControl(&deck,&deck2);
    w.show();
    return a.exec();
    // duel logs
    // bot special minion analysis and summons
    // victory check

}
