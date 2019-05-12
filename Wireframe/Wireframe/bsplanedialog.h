#ifndef BSPLANEDIALOG_H
#define BSPLANEDIALOG_H

#include "settings.h"

#include <QDialog>

namespace Ui {
class BSplaneDialog;
}

class BSplaneDialog : public QDialog
{
    Q_OBJECT

public:
    explicit BSplaneDialog(QWidget *parent = nullptr);
    ~BSplaneDialog();
    Settings* settings;

    void setSettings(Settings *value);

    void buildSplane();

private slots:
    void on_curveSplitBox_valueChanged(int arg1);

    void on_pointRBox_valueChanged(int arg1);

    void on_clearAllButton_clicked();

    void on_deleteButton_toggled(bool checked);

    void on_deleteButton_2_toggled(bool checked);

    void pointCountChanged(int count);

private:
    Ui::BSplaneDialog *ui;

};

#endif // BSPLANEDIALOG_H
