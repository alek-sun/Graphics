#include "mainwindow.h"
#include "ui_mainwindow.h"


using std::cout;
using std:: endl;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    int m = 20, n = 20;
    gameLogic = new GameLogic(m, n);
    ui->scrollAreaWidgetContents->setGameLogic(gameLogic);
    renewSize(m, n);
    timer = new QTimer();
    timer->setInterval(800);
    QObject::connect(timer, SIGNAL(timeout()), this, SLOT(on_actionStep_triggered()));

}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::renewSize(int m, int n)
{
    int r = round(sqrt(3)/2*gameLogic->k);
    int R = gameLogic->k;
    int c = floor(gameLogic->n/2);
    int h = (c + gameLogic->n % 2) * 2*R + c*R + R/2 + 2;
    int w = 2+2*(gameLogic->m)*r;

    ui->scrollAreaWidgetContents->setMinimumSize(w, h);
    ui->scrollAreaWidgetContents->setMaximumSize(w, h);

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
    settings = new SettingsDialog(this);
    settings->setGame(gameLogic);
    settings->exec();
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

void MainWindow::on_actionSave_to_file_triggered()
{
    QUrl fileUrl =
            QFileDialog::getSaveFileUrl(this,
                                        "Open saved model");
                                        //"C:\\1prog\\3course\\graphics\\graphics_fix\\Life3\\Life3\\FIT_16209_ Fediaeva_Life_Data");

    FileDriver fsaver(gameLogic, fileUrl);
    fsaver.saveState();
}

void MainWindow::on_actionOpen_file_triggered()
{
    QUrl fileUrl =
            QFileDialog::getOpenFileUrl(this,
                                        "Open saved model");
                                        //"C:\\1prog\\3course\\graphics\\graphics_fix\\Life3\\Life3\\FIT_16209_ Fediaeva_Life_Data");

    if (fileUrl == QUrl(""))
        return;
    FileDriver fparser(gameLogic, fileUrl);
    vector<pair<int, int>> coords = fparser.parseState();

    ui->scrollAreaWidgetContents->createHexagonField(gameLogic->m, gameLogic->n);

    for (auto xy : coords){
        int c = floor(xy.first/2);
        int x1 = (c + xy.first % 2) * gameLogic->m + c * (gameLogic->m - 1);
        gameLogic->curState[x1+xy.second].setIsAlive(true);
        gameLogic->curState[x1+xy.second].setState(Cell::RECENTLY_BIRTH);
    }

    gameLogic->calculateImpacts();
    renewSize(gameLogic->m, gameLogic->n);
    ui->scrollAreaWidgetContents->repaint();
}

void MainWindow::on_actionGame_parametrs_triggered()
{

}

void MainWindow::on_actionAuhtor_triggered()
{
    AboutDialog about;
    about.exec();
}
