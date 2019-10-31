#include "descriptiondialog.h"
#include "ui_descriptiondialog.h"

DescriptionDialog::DescriptionDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DescriptionDialog)
{
    ui->setupUi(this);    
}

DescriptionDialog::~DescriptionDialog()
{
    delete ui;
}
