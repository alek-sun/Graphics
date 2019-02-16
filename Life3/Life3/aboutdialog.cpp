#include "aboutdialog.h"
#include "ui_aboutdialog.h"
#include <QDebug>

AboutDialog::AboutDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AboutDialog)
{
    ui->setupUi(this);   
    QPixmap pic ("./images/me.jpg");
    ui->pic_label->setPixmap(pic);

}

AboutDialog::~AboutDialog()
{
    delete ui;
}
