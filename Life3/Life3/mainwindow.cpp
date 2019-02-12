#include "mainwindow.h"
#include "ui_mainwindow.h"



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    int m = 10, n = 5;
    gameLogic = new GameLogic(m, n);
    ui->scrollAreaWidgetContents->setGameLogic(gameLogic);
}


MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::resizeEvent(QResizeEvent *)
{
    ui->scrollArea->setMaximumSize(ui->centralWidget->size());
    ui->scrollArea->setMinimumSize(ui->centralWidget->size());
}
