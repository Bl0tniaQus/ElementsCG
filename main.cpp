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
    Card CW(3);
    Card GW(2);
    Card Whirlwind(4);
    CW.setPlace(1);
    GW.setPlace(1);
    duel.getPlayer(0)->summonMinion(&GW,3);
    duel.getPlayer(1)->summonMinion(&CW,2);
    Deck deck;
    duel.getPlayer(0)->setDeck(deck.getDeck(),deck.getDeckSize());
    duel.getPlayer(0)->setDeckOwnership();
    duel.getPlayer(1)->setDeck(deck.getDeck(),deck.getDeckSize());
    duel.getPlayer(1)->setDeckOwnership();
    duel.drawCard(0);
    duel.drawField(0);
    duel.onSpell(&duel.getPlayer(0)->getHand()[0]);
    duel.drawField(0);

    //todo cardowner,GY,decks,hand,draw
    //bot - sprawdzaj wszystkie mozliwosci, zapisuj pierwszy element i stos wyborów
}
