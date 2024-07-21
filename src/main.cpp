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
    QApplication::setStyle(QStyleFactory::create("Fusion"));
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
    QApplication a(argc, argv);
    a.setPalette(darkPalette);
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
