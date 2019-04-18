#ifndef DESCRIPTIONDIALOG_H
#define DESCRIPTIONDIALOG_H

#include <QDialog>

namespace Ui {
class DescriptionDialog;
}

class DescriptionDialog : public QDialog
{
    Q_OBJECT

public:
    explicit DescriptionDialog(QWidget *parent = nullptr);
    ~DescriptionDialog();

private:
    Ui::DescriptionDialog *ui;
};

#endif // DESCRIPTIONDIALOG_H
