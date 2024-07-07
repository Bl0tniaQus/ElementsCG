#include "mainwindow.h"
#include "zone.h"
#include "player.h"
#include "card.h"
#include "duel.h"
#include "time.h"
#include "targetlist.h"
#include "globals.h"
#include "bot.h"
#include <iostream>
#include <QApplication>

int main(int argc, char *argv[])
{
    srand(time(NULL));
   // QApplication a(argc, argv);
   // MainWindow w;
    Duel duel;
    Deck deck(1);
    Deck deck2(2);

    duel.getPlayer(1)->setBot(&bot);
    //duel.DuelControl(&deck,&deck2);
   // w.show();
   // return a.exec();
    //todo poprawić bota, dowiedzieć się dlaczego whirlwind przeciwnego miniona jest gorzej punktowany od cofnięcia swojego
}
