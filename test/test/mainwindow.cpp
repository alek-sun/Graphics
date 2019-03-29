#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QObject::connect(ui->wind, &Wind::sig, this, &MainWindow::recv_sign);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::recv_sign()
{

}
