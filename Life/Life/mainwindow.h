#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <iostream>
#include "imagewidget.h"
#include "gamelogic.h"
#include "cell.h"
#include "settingsdialog.h"
#include <QFileDialog>
#include "fileparser.h"
#include "aboutdialog.h"
#include "gameparamsdialog.h"
#include "descriptiondialog.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void renewSize(int m, int n);
private:
    Ui::MainWindow *ui;
    SettingsDialog* settings;
    GameLogic* gameLogic;
    QTimer* timer;
signals:
protected:
    void resizeEvent(QResizeEvent *);
    void closeEvent(QCloseEvent *event);
private slots:
    void on_actionStep_triggered();
    void on_actionClear_triggered();

    void on_actionGame_settings_triggered();
    void on_actionShow_impact_toggled(bool arg1);

    void on_actionRun_toggled(bool arg1);
    void on_actionReplace_toggled(bool arg1);
    void on_actionSave_to_file_triggered();
    void on_actionOpen_file_triggered();
    void on_actionGame_parametrs_triggered();
    void on_actionAuhtor_triggered();
    void on_actionAbout_game_triggered();
};

#endif // MAINWINDOW_H
