#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "imagewidget.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
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
