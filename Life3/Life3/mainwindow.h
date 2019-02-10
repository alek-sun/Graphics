#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "imagewidget.h"

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
signals:
protected:
    void resizeEvent(QResizeEvent *);
};

#endif // MAINWINDOW_H
