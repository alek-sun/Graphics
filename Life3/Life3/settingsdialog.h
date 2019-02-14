#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QDialog>
#include <QWidget>
#include <QShowEvent>
#include "gamelogic.h"

namespace Ui {
class SettingsDialog;
}

class SettingsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SettingsDialog(QWidget *parent = nullptr);
    ~SettingsDialog();

    void setGame(GameLogic *g);

private:
    Ui::SettingsDialog *ui;
    GameLogic* game;

public slots:
    void on_buttonBox_accepted();

private slots:
    void on_kSlider_valueChanged(int value);
    void on_kEditBox_textChanged(const QString &arg1);
};

#endif // SETTINGSDIALOG_H
