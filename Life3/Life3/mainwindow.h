#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <iostream>
#include "imagewidget.h"
#include "gamelogic.h"
#include "cell.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private:
    Ui::MainWindow *ui;
    GameLogic* gameLogic;
    QTimer* timer;
signals:
protected:
    void resizeEvent(QResizeEvent *);
private slots:
    void on_actionStep_triggered();
    void on_actionClear_triggered();

    void on_actionGame_settings_triggered();
    void on_actionShow_impact_toggled(bool arg1);

    void on_actionRun_toggled(bool arg1);
    void on_actionReplace_toggled(bool arg1);
};

#endif // MAINWINDOW_H
