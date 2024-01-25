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
    duel.getPlayer(0)->setOriginalDeck(deck.getDeck(),deck.getDeckSize());
    duel.getPlayer(0)->setDeckOwnership();
    duel.getPlayer(1)->setOriginalDeck(deck2.getDeck(),deck2.getDeckSize());
    duel.getPlayer(1)->setDeckOwnership();
    duel.drawCard(0); duel.drawCard(1);
    duel.drawCard(0); duel.drawCard(1);
    duel.drawCard(0); duel.drawCard(1);
    duel.playFromHand(duel.getPlayer(0)->getHand()[0]);
    duel.playFromHand(duel.getPlayer(1)->getHand()[0]);
    duel.playFromHand(duel.getPlayer(0)->getHand()[0]);
    duel.drawField(0);
    duel.playFromHand(duel.getPlayer(0)->getHand()[0]);
    duel.drawField(0);
    //zony jak karty na stałe

    //todo cardowner,GY,decks,hand,draw
    //bot - sprawdzaj wszystkie mozliwosci, zapisuj pierwszy element i stos wyborów
}
