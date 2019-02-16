#ifndef GAMEPARAMSDIALOG_H
#define GAMEPARAMSDIALOG_H

#include <QDialog>
#include "gamelogic.h"

using std::string;

namespace Ui {
class GameParamsDialog;
}

class GameParamsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit GameParamsDialog(QWidget *parent = nullptr);
    void setGame(GameLogic* game);
    ~GameParamsDialog();

private slots:
    void on_GameParamsDialog_accepted();

    void on_imp1_edit_textChanged(const QString &arg1);

    void on_imp2_edit_textChanged(const QString &arg1);

    void on_lend_edit_textChanged(const QString &arg1);

    void on_bend_edit_textChanged(const QString &arg1);

    void on_bbegin_edit_textChanged(const QString &arg1);

    void on_lbegon_edit_textChanged(const QString &arg1);

    void on_imp2_slider_valueChanged(int value);

    void on_imp1_slider_valueChanged(int value);

    bool isDigit(QString s);

private:
    Ui::GameParamsDialog *ui;
    GameLogic* game;
};

#endif // GAMEPARAMSDIALOG_H
