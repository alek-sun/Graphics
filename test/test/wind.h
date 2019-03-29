#ifndef WIND_H
#define WIND_H

#include <QWidget>

class Wind : public QWidget
{
    Q_OBJECT
public:
    explicit Wind(QWidget *parent = nullptr);

Q_SIGNALS:
    void sig();

public slots:
};

#endif // WIND_H
