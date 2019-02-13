#include "mainwindow.h"
#include "ui_mainwindow.h"

using std::cout;
using std:: endl;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    int m = 10, n = 10;
    gameLogic = new GameLogic(m, n);
    ui->scrollAreaWidgetContents->setGameLogic(gameLogic);
    timer = new QTimer();
    timer->setInterval(500);
    QObject::connect(timer, SIGNAL(timeout()), this, SLOT(on_actionStep_triggered()));

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

void MainWindow::on_actionClear_triggered()
{
    gameLogic->clear();
    ui->scrollAreaWidgetContents->repaint();
}


void MainWindow::on_actionGame_settings_triggered()
{

}

void MainWindow::on_actionShow_impact_toggled(bool checked)
{
    if (checked){
        ui->scrollAreaWidgetContents->displayImpact = true;
        ui->scrollAreaWidgetContents->repaint();
    } else {
        ui->scrollAreaWidgetContents->displayImpact = false;
        ui->scrollAreaWidgetContents->repaint();
    }
}


void MainWindow::on_actionRun_toggled(bool checked)
{
    if (checked){
        timer->start();
    } else {
        timer->stop();
    }
}

void MainWindow::on_actionReplace_toggled(bool checked)
{
    if (checked){
        gameLogic->mode = GameLogic::XOR_MODE;
    } else {
        gameLogic->mode = GameLogic::REPLACE_MODE;
    }
}
