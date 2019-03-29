#ifndef BACKGROUNDWIDGET_H
#define BACKGROUNDWIDGET_H

#include <QWidget>
#include <QLabel>
#include "isolinewidget.h"

class BackgroundWidget : public QWidget
{
    Q_OBJECT
public:
    explicit BackgroundWidget(QWidget *parent = nullptr);
    void setSettings(Settings *value);

private:
    QImage background;
    Settings* settings;

    int abX, abY, cdX, cdY;
    double w, h;
    int n_ab, n_cd;
    void redrawGrid();

Q_SIGNALS:
protected:
    void paintEvent(QPaintEvent* event);

public slots:
};

#endif // BACKGROUNDWIDGET_H
