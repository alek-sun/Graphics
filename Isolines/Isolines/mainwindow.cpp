#include "aboutdialog.h"
#include "filedriver.h"
#include "mainwindow.h"
#include "settingsdialog.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <QDebug>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    settings = ui->isoline_widget->settings;
    ui->background_widget->setSettings(settings);
    ui->legend_widget->setSettings(settings);
    fx = new FCalculator(settings);
    ui->isoline_widget->setFx(fx);

    double lim_x, lim_y;
    fx->getFLimits(&lim_x, &lim_y);

    QObject::connect(ui->isoline_widget, &IsolineWidget::mouseMoved, this, &MainWindow::positionPerformed);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionOpen_triggered()
{
    QUrl fileUrl =
            QFileDialog::getOpenFileUrl(this,
                                        "Open file",
                                        QUrl("FIT_16209_ Fediaeva_Isolines_Data"));

    if (fileUrl == QUrl(""))
        return;

    FileDriver fparser(fileUrl);
    if (fparser.parseSettings(settings)){
        ui->actionShow_grid->setEnabled(true);
        ui->actionShow_isolines->setEnabled(true);
        ui->actionColor_Map_Interpolation->setEnabled(true);
        ui->actionShow_isolines->setEnabled(true);
        ui->actionInteractive_isoline_draw->setEnabled(true);
        ui->actionShow_intersection_points->setEnabled(true);
        settings->changed = true;
    } else {
        QMessageBox b;
        b.setWindowTitle("Oops..");
        b.setText("Incorrect file format. Please, select less than 25 colors and use color interpolation mode.");
        b.exec();
    }
}

void MainWindow::on_actionAuthor_triggered()
{
    AboutDialog a;
    a.exec();
}

void MainWindow::on_actionSettings_triggered()
{
    SettingsDialog settingsDialog;
    settingsDialog.setSettings(settings);
    settingsDialog.exec();
}

void MainWindow::on_actionInteractive_isoline_draw_toggled(bool val)
{
    ui->isoline_widget->mods->interactive = val;
    if (val){
        settings->userIsolines.clear();
    }
    repaint();
}

void MainWindow::on_actionShow_grid_toggled(bool val)
{    
     ui->isoline_widget->mods->gridShow = val;
     ui->isoline_widget->repaint();
}

void MainWindow::on_actionColor_Map_Interpolation_toggled(bool val)
{   
    ui->isoline_widget->mods->interpolation = val;
    settings->changed = true;
    ui->legend_widget->interpolation = val;
    ui->legend_widget->repaint();
    ui->isoline_widget->repaint();
}

void MainWindow::on_actionShow_isolines_toggled(bool val)
{

     ui->isoline_widget->mods->showIsolines = val;
     if (!val){
         settings->userIsolines.clear();
     }
     ui->isoline_widget->repaint();
}

void MainWindow::positionPerformed(IsolineWidget::Position *pos)
{
    QString msg;
    msg.append("x = ").append(QString::number(pos->x, 'd', 2));
    msg.append("    y = ").append(QString::number(pos->y, 'd', 2));
    msg.append("    f(x,y) = ").append(QString::number(pos->f, 'd', 2));

    ui->statusBar->showMessage(msg);
}

void MainWindow::on_actionShow_intersection_points_toggled(bool val)
{
    ui->isoline_widget->mods->showIntersections = val;
    ui->isoline_widget->repaint();
}
