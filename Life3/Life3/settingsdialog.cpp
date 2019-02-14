#include "settingsdialog.h"
#include "settingsdialog.h"
#include "ui_settingsdialog.h"

SettingsDialog::SettingsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingsDialog)
{
    ui->setupUi(this);
    ui->kSlider->setMaximum(60);
    ui->kSlider->setMinimum(5);
}

SettingsDialog::~SettingsDialog()
{
    delete ui;
}

void SettingsDialog::setGame(GameLogic *g)
{
    game = g;
    ui->kEditBox->setText(QString::number(game->k));
    ui->m_edit->setText(QString::number(game->m));
    ui->n_edit->setText(QString::number(game->n));
    ui->kSlider->setValue(game->k);
    if (game->mode == GameLogic::REPLACE_MODE){
        ui->replase_button->setChecked(true);
    } else {
        ui->xor_button->setChecked(true);
    }
}

void SettingsDialog::on_buttonBox_accepted()
{
    int buf = ui->kEditBox->text().toInt();
    if (game->k != buf){
        game->paramsChanged = true;
        game->k = buf;
    }

    buf = ui->m_edit->text().toInt();
    if (game->m != buf){
        game->paramsChanged = true;
        game->newM = buf;
    }

    buf = ui->n_edit->text().toInt();
    if (game->n != buf){
        game->paramsChanged = true;
        game->newN = buf;
    }

    if (ui->replase_button->isChecked()){
        game->mode = GameLogic::REPLACE_MODE;
    } else {
        game->mode = GameLogic::XOR_MODE;
    }
}


void SettingsDialog::on_kSlider_valueChanged(int value)
{
    ui->kEditBox->setText(QString::number(value));
}

void SettingsDialog::on_kEditBox_textChanged(const QString &str)
{
    ui->kSlider->setValue(str.toInt());
}
