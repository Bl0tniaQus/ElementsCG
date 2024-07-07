#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(findChild<QPushButton*>("testButton"), &QPushButton::released, this, &MainWindow::startDuel);
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::startDuel()
{
    //findChild<QStackedWidget*>("stackedWidget")->setCurrentIndex(1);
}


