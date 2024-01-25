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
    duel.drawCard(0);
    duel.playFromHand(duel.getPlayer(0)->getHand()[0]);
    duel.drawField(0); std::cout<<"Hand: ";
    for (int i=0;i<duel.getPlayer(0)->getHandSize();i++)
    {
        std::cout<<duel.getPlayer(0)->getHand()[i]->getName()<<"; ";
    }std::cout<<std::endl<<"Field: ";
    for (int i=0;i<5;i++)
    {
        if (duel.getPlayer(0)->getMinionField()[i].getCard()!=nullptr)
        std::cout<<duel.getPlayer(0)->getMinionField()[i].getCard()->getName()<<"; ";
    }std::cout<<std::endl;
    //todo cardowner,GY,decks,hand,draw
    //bot - sprawdzaj wszystkie mozliwosci, zapisuj pierwszy element i stos wyborów
}
