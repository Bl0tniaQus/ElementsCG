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
    duel.drawField(0);
    Card CW(1);
    Card GW(2);
    CW.setPlace(1);
    GW.setPlace(1);
    duel.getPlayer(0)->summonMinion(&GW,3);
    duel.drawField(0);
    duel.getPlayer(1)->summonMinion(&CW,2);
    duel.drawField(0);
    duel.combat(duel.getPlayer(0)->getMinionField()[3].getCard(),duel.getPlayer(1)->getMinionField()[2].getCard());
    duel.drawField(0);
    Deck deck;
    duel.getPlayer(0)->setDeck(deck.getDeck(),7);
    duel.drawCard(0);
    std::cout<<duel.getPlayer(0)->getHand()[duel.getPlayer(0)->getHandSize()-1].getName();
    //todo cardowner,GY,decks,hand,draw
}
