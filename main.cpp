#include "mainwindow.h"
#include "zone.h"
#include "spellzone.h"
#include "minionzone.h"
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
    Deck deck;
    Deck deck2;
    /*
    Player* player1 = duel.getPlayer(0);
    Player* player2 = duel.getPlayer(1);
    duel.drawCard(player1); duel.drawCard(player2);
    duel.drawCard(player1); duel.drawCard(player2);
    duel.drawCard(player1); duel.drawCard(player2);
    duel.drawCard(player1);
    duel.playFromHand(duel.getPlayer(0)->getHand()[0]);
    duel.playFromHand(duel.getPlayer(0)->getHand()[0]);
    duel.playFromHand(duel.getPlayer(1)->getHand()[0]);
    duel.playFromHand(duel.getPlayer(1)->getHand()[0]);
    duel.drawField(0);
    duel.summonSpecialMinion(duel.getPlayer(0)->getSpecialDeck()[0]);
    //duel.playFromHand(duel.getPlayer(0)->getHand()[0]);
    duel.drawField(0);
    duel.playFromHand(duel.getPlayer(0)->getHand()[0]);*/
    duel.getPlayer(1)->setBot();
    duel.DuelControl(&deck,&deck2);




    //todo Servants, multiple targeting, duel control
    //lingering and continuous effects, effect negation, stats and element manipulation, search and tutoring
    //bot - create a sandbox-like copy of a gamestate, calculate position factor(s), then check all possible moves,
    //calculate factor(s) for new gamestates and perform best action on real gamestate
    //goal - make it possible to play full duel with AI in cli, then proceed with gui

    //servants - remove from servant deck, bounce to servant deck,

}
