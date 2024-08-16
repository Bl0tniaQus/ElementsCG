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
    w.show();
    return a.exec();
}
