#include "bsplanedialog.h"
#include "ui_bsplanedialog.h"
#include <QDebug>

BSplaneDialog::BSplaneDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::BSplaneDialog)
{
    ui->setupUi(this);
    connect(ui->widget, &BSplaneWidget::pointCountChanged, this, &BSplaneDialog::pointCountChanged);
    ui->widget->setCursor(Qt::PointingHandCursor);
}

BSplaneDialog::~BSplaneDialog()
{
    delete ui;
}

void BSplaneDialog::setSettings(Settings *value)
{
    settings = value;
    ui->widget->setSettings(value);
    ui->curveSplitBox->setValue(settings->nCurveSplit);
    ui->pointRBox->setValue(settings->pointR);
    ui->countLabel->setText(QString::number(settings->bearingPoints.size()));
}

void BSplaneDialog::buildSplane()
{
    ui->widget->drawSplane();
}

void BSplaneDialog::on_curveSplitBox_valueChanged(int val)
{
    settings->nCurveSplit = val;
    ui->widget->repaint();
}

void BSplaneDialog::on_pointRBox_valueChanged(int v)
{
    settings->pointR = v;
    repaint();
}

void BSplaneDialog::on_clearAllButton_clicked()
{
    settings->bearingPoints.clear();
    pointCountChanged(0);
    repaint();
}

void BSplaneDialog::on_deleteButton_toggled(bool checked)
{
    ui->deleteButton_2->setChecked(false);
    ui->widget->deleteMode = checked;
    ui->widget->addPointMode = checked ? false : ui->widget->addPointMode;
}

void BSplaneDialog::on_deleteButton_2_toggled(bool checked)
{
     ui->deleteButton->setChecked(false);
     ui->widget->addPointMode = checked;
     ui->widget->deleteMode = checked ? false : ui->widget->deleteMode;
}

void BSplaneDialog::pointCountChanged(int count)
{
    ui->countLabel->setText(QString::number(count));
}
