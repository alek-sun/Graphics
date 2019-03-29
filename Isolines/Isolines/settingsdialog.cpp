#include "settingsdialog.h"
#include "ui_settingsdialog.h"

SettingsDialog::SettingsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingsDialog)
{
    ui->setupUi(this);
}

SettingsDialog::~SettingsDialog()
{
    delete ui;
}

void SettingsDialog::setSettings(Settings *value)
{
    settings = value;
    ui->kBox->setValue(settings->k);
    ui->mBox->setValue(settings->m);
    ui->aBox->setValue(settings->a);
    ui->bBox->setValue(settings->b);
    ui->cBox->setValue(settings->c);
    ui->dBox->setValue(settings->d);
}

void SettingsDialog::on_buttonBox_accepted()
{
    settings->k = ui->kBox->value();
    settings->m = ui->mBox->value();
    settings->a = ui->aBox->value();
    settings->b = ui->bBox->value();
    settings->c = ui->cBox->value();
    settings->d = ui->dBox->value();
    settings->changed = true;
}

void SettingsDialog::on_cBox_valueChanged(double val)
{
    ui->buttonBox->setEnabled(val < ui->dBox->value());
}

void SettingsDialog::on_dBox_valueChanged(double val)
{
    ui->buttonBox->setEnabled(val > ui->cBox->value());
}

void SettingsDialog::on_aBox_valueChanged(double val)
{
    ui->buttonBox->setEnabled(val < ui->bBox->value());
}

void SettingsDialog::on_bBox_valueChanged(double val)
{
    ui->buttonBox->setEnabled(val > ui->aBox->value());
}
