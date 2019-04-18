#include "gameparamsdialog.h"
#include "ui_gameparamsdialog.h"

GameParamsDialog::GameParamsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GameParamsDialog)
{
    ui->setupUi(this);
    ui->imp1_slider->setRange(0.0, 10.0);
    ui->imp2_slider->setRange(0.0, 10.0);
}

void GameParamsDialog::setGame(GameLogic *game)
{
    this->game = game;
    ui->imp1_edit->setText(QString::number(game->firstImpact));
    ui->imp2_edit->setText(QString::number(game->secondImpact));

    ui->lbegon_edit->setText(QString::number(game->liveBegin));
    ui->lend_edit->setText(QString::number(game->liveEnd));
    ui->bbegin_edit->setText(QString::number(game->birthBegin));
    ui->bend_edit->setText(QString::number(game->birthEnd));
}

GameParamsDialog::~GameParamsDialog()
{
    delete ui;
}

void GameParamsDialog::on_GameParamsDialog_accepted()
{
    game->firstImpact = ui->imp1_edit->text().toDouble();
    game->secondImpact = ui->imp2_edit->text().toDouble();

    game->liveBegin = ui->lbegon_edit->text().toDouble();
    game->liveEnd = ui->lend_edit->text().toDouble();
    game->birthBegin = ui->bbegin_edit->text().toDouble();
    game->birthEnd = ui->bend_edit->text().toDouble();
}

bool isDigit(QString s){
    string str = s.toStdString();
    char *p;
    strtol(str.c_str(), &p, 10);
    return (*p == 0);
}

void GameParamsDialog::on_imp1_edit_textChanged(const QString &str)
{
    ui->imp1_slider->setValue(round(str.toDouble()));

    if (!isDigit(str) || str.toDouble() > 50.0 || str.toDouble() < 0.0){
        ui->buttonBox->setDisabled(true);
    } else {
        ui->buttonBox->setDisabled(false);
    }
}

void GameParamsDialog::on_imp2_edit_textChanged(const QString &str)
{
    ui->imp2_slider->setValue(str.toDouble());

    if (!isDigit(str) || str.toDouble() > 50.0 || str.toDouble() < 0.0){
        ui->buttonBox->setDisabled(true);
    } else {
        ui->buttonBox->setDisabled(false);
    }
}

void GameParamsDialog::on_lend_edit_textChanged(const QString &str)
{
    if (!isDigit(str)){
        ui->buttonBox->setDisabled(true);
        return;
    }

    double bend = ui->bend_edit->text().toDouble();
    double bbegin = ui->bbegin_edit->text().toDouble();
    double lbegin = ui->lbegon_edit->text().toDouble();

    double d = str.toDouble();
     if (d > 50.0 || d < 0.0 || d < bend || d < bbegin || d < lbegin){
        ui->buttonBox->setDisabled(true);
    } else {
        ui->buttonBox->setDisabled(false);
    }
}

void GameParamsDialog::on_bend_edit_textChanged(const QString &str)
{
    if (!isDigit(str)){
        ui->buttonBox->setDisabled(true);
        return;
    }

    double lend = ui->lend_edit->text().toDouble();
    double bbegin = ui->bbegin_edit->text().toDouble();
    double lbegin = ui->lbegon_edit->text().toDouble();

    double d = str.toDouble();
     if (d > 50.0 || d < 0.0 || d > lend || d < bbegin || d < lbegin){
        ui->buttonBox->setDisabled(true);
    } else {
        ui->buttonBox->setDisabled(false);
    }
}

void GameParamsDialog::on_bbegin_edit_textChanged(const QString &str)
{
    if (!isDigit(str)){
        ui->buttonBox->setDisabled(true);
        return;
    }

    double lend = ui->lend_edit->text().toDouble();
    double bend = ui->bend_edit->text().toDouble();
    double lbegin = ui->lbegon_edit->text().toDouble();

    double d = str.toDouble();
     if (d > 50.0 || d < 0.0 || d > lend || d > bend || d < lbegin){
        ui->buttonBox->setDisabled(true);
    } else {
        ui->buttonBox->setDisabled(false);
    }
}

void GameParamsDialog::on_lbegon_edit_textChanged(const QString &str)
{
    if (!isDigit(str)){
        ui->buttonBox->setDisabled(true);
        return;
    }

    double lend = ui->lend_edit->text().toDouble();
    double bend = ui->bend_edit->text().toDouble();
    double bbegin = ui->bbegin_edit->text().toDouble();

    double d = str.toDouble();
     if (d > 50.0 || d < 0.0 || d > lend || d > bend || d > bbegin){
        ui->buttonBox->setDisabled(true);
    } else {
        ui->buttonBox->setDisabled(false);
    }
}

void GameParamsDialog::on_imp2_slider_valueChanged(int value)
{
    ui->imp2_edit->setText(QString::number(value));
}

void GameParamsDialog::on_imp1_slider_valueChanged(int value)
{
    ui->imp1_edit->setText(QString::number(value));
}

bool GameParamsDialog::isDigit(QString s)
{
    bool sucs;
    s.toDouble(&sucs);
    return sucs;
}
