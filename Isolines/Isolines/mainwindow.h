#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "backgroundwidget.h"
#include "isolinewidget.h"

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
    void on_actionOpen_triggered();

    void on_actionAuthor_triggered();

    void on_actionSettings_triggered();

    void on_actionInteractive_isoline_draw_toggled(bool arg1);

    void on_actionShow_grid_toggled(bool arg1);

    void on_actionColor_Map_Interpolation_toggled(bool arg1);

    void on_actionShow_isolines_toggled(bool arg1);

    void positionPerformed(IsolineWidget::Position*);

    void on_actionShow_intersection_points_toggled(bool arg1);

private:
    Ui::MainWindow *ui;
    Settings *settings;
    FCalculator* fx;
    BackgroundWidget * backgroud_w;
};

#endif // MAINWINDOW_H
