#include "mainwindow.h"
#include "zone.h"
#include "player.h"
#include "card.h"
#include "duel.h"
#include "cardcatalog.h"
#include <iostream>
#include <QApplication>

int main(int argc, char *argv[])
{
    //QApplication a(argc, argv);
    //MainWindow w;
    //w.show();
    //return a.exec();
    Duel duel;
    Deck deck(1);
    Deck deck2(2);
    duel.getPlayer(1)->setBot();
    duel.DuelControl(&deck,&deck2);

    //lingering and continuous effects, effect negation, stats and element manipulation, search and tutoring
    //bot - create a sandbox-like copy of a gamestate, calculate position factor(s), then check all possible moves,
    //calculate factor(s) for new gamestates and perform best action on real gamestate
    //goal - make it possible to play full duel with AI in cli, then proceed with gui

    //servants - remove from servant deck, bounce to servant deck,

}
