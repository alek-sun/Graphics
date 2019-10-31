#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "awidget.h"
#include "bwidget.h"
#include "cwidget.h"
#include "filedriver.h"
#include "rotationdialog.h"

#include <QMainWindow>
#include <QDebug>
#include <QFileDialog>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    CWidget::Settings* settings;

private:
    QImage* origImage;

private slots:

    void on_actionClear_triggered();

    void awidget_selected(int , int , int , int );

    void on_actionBW_triggered();

    void on_actionNegative_triggered();

    void on_actionOrdered_dither_triggered();

    void on_actionSave_triggered();

    void on_actionOpen_triggered();

    void on_actionSelect_square_toggled(bool arg1);

    void on_actionR2Bmp_triggered();    

    void on_actionBlur_triggered();    

    void on_actionRoberts_triggered();

    void on_actionError_diffusion_dither_triggered();

    void on_actionWatercoloring_triggered();

    void on_actionStamping_triggered();

    void on_actionSobel_triggered();

    void on_actionAuthor_triggered();

    void on_actionSettings_triggered();

    void on_actionDuplication_triggered();

    void on_actionGamma_correction_triggered();

    void on_actionSharpness_triggered();

    void on_actionConstriction_triggered();

    void on_actionErozy_triggered();

private:
    Ui::MainWindow *ui;
    AWidget* aw;
    BWidget* bw;
    CWidget* cw;
    double k;   // compression

};

#endif // MAINWINDOW_H
