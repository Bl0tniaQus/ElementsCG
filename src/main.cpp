#include "engine/duel.h"
#include "engine/globals.h"
#include "ui/mainwindow.h"
#include <iostream>
#include <QApplication>
#include <QDebug>
#include <QStyleFactory>
int main(int argc, char *argv[])
{
    srand(time(NULL));
   /* Duel* duel = new Duel;
    duel->getPlayer(1)->setBot(&bot);
    Deck* deck = new Deck(0);
    Deck* deck2 = new Deck(0);
    duel->DuelControl(deck, deck2);
    delete deck;
    delete deck2;*/
    QApplication a(argc, argv);
    //shoutout to QuantumCD for theme
    //https://gist.github.com/QuantumCD/6245215
    a.setStyle(QStyleFactory::create("Fusion"));
    QPalette darkPalette;
    darkPalette.setColor(QPalette::Window, QColor(53,53,53));
    darkPalette.setColor(QPalette::WindowText, Qt::white);
    darkPalette.setColor(QPalette::Base, QColor(25,25,25));
    darkPalette.setColor(QPalette::AlternateBase, QColor(53,53,53));
    darkPalette.setColor(QPalette::ToolTipBase, Qt::white);
    darkPalette.setColor(QPalette::ToolTipText, Qt::white);
    darkPalette.setColor(QPalette::Text, Qt::white);
    darkPalette.setColor(QPalette::Button, QColor(53,53,53));
    darkPalette.setColor(QPalette::ButtonText, Qt::white);
    darkPalette.setColor(QPalette::BrightText, Qt::red);
    darkPalette.setColor(QPalette::Link, QColor(42, 130, 218));

    darkPalette.setColor(QPalette::Highlight, QColor(42, 130, 218));
    darkPalette.setColor(QPalette::HighlightedText, Qt::black);

    a.setPalette(darkPalette);

    a.setStyleSheet("QToolTip { color: #ffffff; background-color: #2a82da; border: 1px solid white; }");
    MainWindow w;
    w.show();
    return a.exec();

}
//TODO major target lists refatoring, wind up restart effect
//TODO copy card properties in gamestate
//TODO deck copy(utwórz, połącz, utwórz połączenie)
//TODO use new deck constructor
//TODO fix leak after duel
//TODO bot nie działa gdy ma pierwszą turę
