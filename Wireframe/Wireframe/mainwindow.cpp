#include "aboutdialog.h"
#include "bsplanedialog.h"
#include "bsplanewidget.h"
#include "filedriver.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    settings = new Settings();
    ui->widget->s = settings;
    ui->circleHidingBox->setValue(settings->hidingAngle);
    ui->splaneHidingBox->setValue(settings->hidingSplane);

    ui->sliderCircleN->setValue(settings->angleN);
    ui->spinCircleN->setValue(settings->angleN);

    ui->sliderSplaneN->setValue(settings->splaneN);
    ui->spinSplaneN->setValue(settings->splaneN);
    startPack();
    connect(ui->widget, &WireframeWidget::angleChanged, this, &MainWindow::angleChanged);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::angleChanged(int x, int y, int z)
{
    ui->x_label->setText(QString::number(x));
    ui->y_label->setText(QString::number(y));
    ui->z_label->setText(QString::number(z));
}

void MainWindow::on_actionBuild_B_splane_triggered()
{
    BSplaneDialog w;
    w.setSettings(settings);
    w.exec();
}

void MainWindow::on_actionAuthor_triggered()
{
    AboutDialog d;
    d.exec();
}

void MainWindow::on_splaneHidingBox_valueChanged(int val)
{
    settings->hidingSplane = val;
    repaint();
}

void MainWindow::on_circleHidingBox_valueChanged(int val)
{
    settings->hidingAngle = val;
    repaint();
}

void MainWindow::on_sliderSplaneN_valueChanged(int value)
{
    ui->spinSplaneN->setValue(value);
    settings->splaneN = value;
    repaint();
}

void MainWindow::on_sliderCircleN_valueChanged(int value)
{
    ui->spinCircleN->setValue(value);
    settings->angleN = value;
    repaint();
}

void MainWindow::on_spinSplaneN_valueChanged(int value)
{
    ui->sliderSplaneN->setValue(value);
    settings->splaneN = value;
    repaint();
}

void MainWindow::on_spinCircleN_valueChanged(int value)
{
    ui->sliderCircleN->setValue(value);
    settings->angleN = value;
    repaint();
}

void MainWindow::on_actionSave_triggered()
{
    QUrl fileUrl =
            QFileDialog::getSaveFileUrl(this,
                                        "Save to file",
                                        QUrl("Models"));

    if (fileUrl == QUrl(""))
        return;

    FileDriver d(fileUrl);
    d.saveModel(*settings);
}

void MainWindow::on_actionOpen_triggered()
{
    QUrl fileUrl =
            QFileDialog::getOpenFileUrl(this,
                                        "Open file",
                                        QUrl("Models"));

    if (fileUrl == QUrl(""))
        return;

    FileDriver fparser(fileUrl);
    fparser.openModel(settings);
    BSplaneDialog splaneDialog;
    splaneDialog.setSettings(settings);
    splaneDialog.buildSplane();
}

void MainWindow::startPack()
{
    BSplaneDialog b;
    settings->bearingPoints.push_back(new QVector2D(8, 34));
    settings->bearingPoints.push_back(new QVector2D(14, 245));
    settings->bearingPoints.push_back(new QVector2D(93, 55));
    settings->bearingPoints.push_back(new QVector2D(221, 216));
    settings->bearingPoints.push_back(new QVector2D(360, 172));
    settings->bearingPoints.push_back(new QVector2D(570, 147));
    settings->bearingPoints.push_back(new QVector2D(571, 61));
    settings->bearingPoints.push_back(new QVector2D(595, 24));
    b.setSettings(settings);
    b.buildSplane();
}

void MainWindow::on_pushButton_clicked()
{
    ui->widget->angleX = 0;
    ui->widget->angleY = 0;
    ui->widget->angleZ = 0;
    ui->x_label->setNum(0);
    ui->y_label->setNum(0);
    ui->z_label->setNum(0);
    ui->widget->repaint();
}
