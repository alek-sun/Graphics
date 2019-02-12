#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
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
signals:
protected:
    void resizeEvent(QResizeEvent *);
private slots:
    void on_actionStep_triggered();
};

#endif // MAINWINDOW_H
