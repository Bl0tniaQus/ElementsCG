#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "dueluibridge.h"

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow)
{
    this->ui->setupUi(this);
    this->setFixedSize(1600,900);
    this->ui->stackedWidget->setCurrentIndex(0);
    connect(findChild<QPushButton*>("testButton"), &QPushButton::released, this, &MainWindow::startDuel);
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::startDuel()
{
    this->ui->stackedWidget->setCurrentIndex(1);
    QPixmap pm("/home/blotniak/Pulpit/ElementsCG Grafika/jpegs/dragonoidwarrior.jpg");
    QPixmap empty;
   // DuelUiBridge dub(new Duel, this->ui);
    QLabel** labels = new QLabel* [10];
    for (int i=0;i<10;i++)
    {
        labels[i] = new QLabel(ui->scrollArea);
        labels[i]->setPixmap(pm);
        labels[i]->setGeometry(QRect(i*80,0,80,80));
        labels[i]->setScaledContents(true);
        labels[i]->setVisible(true);
        labels[i]->setContentsMargins(10,10,10,10);
    }
    ui->scrollAreaWidgetContents->setGeometry(20,20,800,80);
    //ui->scrollAreaWidgetContents->setContentsMargins(20,20,20,20);
    //label->setFrameStyle(QFrame::Panel | QFrame::Sunken);
   // label->setAlignment(Qt::AlignBottom | Qt::AlignRight);
    //label->setParent(ui->scrollArea);
    this->ui->oppZ0Image->setPixmap(pm);
   // label->setText("test");
   // label->setVisible(true);
   // label->setGeometry(QRect(10,10,30,80));

    this->ui->oppZ0Image->setPixmap(empty);
    this->ui->oppZ0Label->setText("L10 10/10 B1 A1 SI N");
    this->ui->oppZ0Image->setScaledContents(true);

}


