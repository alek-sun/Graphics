#include "descriptiondialog.h"
#include "ui_descriptiondialog.h"

DescriptionDialog::DescriptionDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DescriptionDialog)
{
    ui->setupUi(this);
    setStyleSheet("background-color: rgba(245, 245, 245, 245);");
}

DescriptionDialog::~DescriptionDialog()
{
    delete ui;
}
