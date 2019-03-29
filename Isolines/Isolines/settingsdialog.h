#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include "settings.h"

#include <QDialog>

namespace Ui {
class SettingsDialog;
}

class SettingsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SettingsDialog(QWidget *parent = nullptr);
    ~SettingsDialog();

    void setSettings(Settings *value);

private slots:
    void on_buttonBox_accepted();

    void on_cBox_valueChanged(double arg1);

    void on_dBox_valueChanged(double arg1);

    void on_aBox_valueChanged(double arg1);

    void on_bBox_valueChanged(double arg1);

private:
    Ui::SettingsDialog *ui;
    Settings* settings;
};

#endif // SETTINGSDIALOG_H
