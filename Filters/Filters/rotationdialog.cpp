#include "rotationdialog.h"
#include "ui_rotationdialog.h"


RotationDialog::RotationDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RotationDialog)
{
    ui->setupUi(this);
}

RotationDialog::~RotationDialog()
{
    delete ui;
}

void RotationDialog::setSettings(CWidget::Settings* s)
{
    ui->dial_angle->setValue(s->angle);
    ui->angle->setText(QString::number(s->angle));
    ui->dial_sobel->setValue(s->sobel);
    ui->sobel->setText(QString::number(s->sobel));
    ui->dial_robert->setValue(s->angle);
    ui->robert->setText(QString::number(s->roberts));
    ui->gammaSlider->setValue(s->gamma*100);
    ui->gamma->setText(QString::number(s->gamma));
    this->s = s;
}

void RotationDialog::on_buttonBox_accepted()
{
    if (s->angle != ui->dial_angle->value()
            || s->angle != ui->dial_angle->value()
            || s->roberts != ui->dial_robert->value()
            || s->gamma != (ui->gamma->text()).toDouble()) {
        s->changed = true;
    }
    s->angle = ui->dial_angle->value();
    s->sobel = ui->dial_sobel->value();
    s->roberts = ui->dial_robert->value();
    s->gamma = (ui->gamma->text()).toDouble();
}

void RotationDialog::on_angle_textChanged(const QString &val)
{
    ui->dial_angle->setValue(val.toInt());
}

void RotationDialog::on_dial_angle_valueChanged(int value)
{
    ui->angle->setText(QString::number(value));
}

void RotationDialog::on_dial_robert_valueChanged(int value)
{
    ui->robert->setText(QString::number(value));
}

void RotationDialog::on_dial_sobel_valueChanged(int value)
{
    ui->sobel->setText(QString::number(value));
}

void RotationDialog::on_robert_textChanged(const QString &val)
{
    ui->dial_robert->setValue(val.toInt());
}


void RotationDialog::on_sobel_textChanged(const QString &val)
{
    ui->dial_sobel->setValue(val.toInt());
}

void RotationDialog::on_gammaSlider_valueChanged(int value)
{
    ui->gamma->setText(QString::number(value/100.0));
}


void RotationDialog::on_gamma_textEdited(const QString &val)
{
     ui->gammaSlider->setValue(val.toDouble()*100.0);
     if (val.toDouble() < 0.3){
         ui->buttonBox->setEnabled(false);
     } else {
         ui->buttonBox->setEnabled(true);
     }
}
