#ifndef ROTATIONDIALOG_H
#define ROTATIONDIALOG_H

#include "cwidget.h"
#include <QDialog>

namespace Ui {
class RotationDialog;
}

class RotationDialog : public QDialog
{
    Q_OBJECT

public:
    explicit RotationDialog(QWidget *parent = nullptr);

    ~RotationDialog();
    void setSettings(CWidget::Settings *s);


private slots:
    void on_buttonBox_accepted();   

    void on_angle_textChanged(const QString &arg1);

    void on_dial_angle_valueChanged(int value);

    void on_dial_robert_valueChanged(int value);

    void on_dial_sobel_valueChanged(int value);

    void on_robert_textChanged(const QString &arg1);

    void on_sobel_textChanged(const QString &arg1);

    void on_gammaSlider_valueChanged(int value);

    void on_gamma_textEdited(const QString &arg1);

private:
    Ui::RotationDialog *ui;
    CWidget::Settings *s;
};

#endif // ROTATIONDIALOG_H
