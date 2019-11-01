#include "aboutdialog.h"
#include "ui_aboutdialog.h"

AboutDialog::AboutDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AboutDialog)
{
    ui->setupUi(this);
    //QPixmap pic ("./images/me.jpg");
    //ui->photo->setPixmap(pic);
}

AboutDialog::~AboutDialog()
{
    delete ui;
}
