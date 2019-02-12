#include "mainwindow.h"
#include "ui_mainwindow.h"



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    int m = 11, n = 6;
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

void MainWindow::on_actionStep_triggered()
{
    gameLogic->step();
    ui->scrollAreaWidgetContents->repaint();
}
