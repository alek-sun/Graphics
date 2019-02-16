#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QDialog>
#include <QWidget>
#include <QShowEvent>
#include <QIntValidator>
#include <QMessageBox>
#include <ctype.h>
#include "gamelogic.h"

using std::string;

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
    bool isDigit(QString s){
        bool sucs;
        s.toDouble(&sucs);
        return sucs;
    }
    void on_m_edit_textChanged(const QString &arg1);
    void on_n_edit_textChanged(const QString &arg1);
};

#endif // SETTINGSDIALOG_H
