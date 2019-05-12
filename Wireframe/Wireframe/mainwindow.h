#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "settings.h"

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void angleChanged(int x, int y, int z);
    void on_actionBuild_B_splane_triggered();
    void on_actionAuthor_triggered();

    void on_splaneHidingBox_valueChanged(int arg1);

    void on_circleHidingBox_valueChanged(int arg1);

    void on_sliderSplaneN_valueChanged(int value);

    void on_sliderCircleN_valueChanged(int value);

    void on_spinSplaneN_valueChanged(int arg1);

    void on_spinCircleN_valueChanged(int arg1);

    void on_actionSave_triggered();

    void on_actionOpen_triggered();

    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    Settings* settings;

    void startPack();
};

#endif // MAINWINDOW_H
