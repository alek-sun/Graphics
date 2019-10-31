#include "aboutdialog.h"
#include "filedriver.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    aw = ui->a_widget;
    bw = ui->b_widget;
    cw = ui->c_widget;
    origImage = new QImage(350, 350, QImage::Format_ARGB32);
    origImage->fill(QColor(255,255,255,255));
    QObject::connect(ui->a_widget, &AWidget::selected, this, &MainWindow::awidget_selected);
    settings = cw->settings;
}

MainWindow::~MainWindow()
{
    delete aw;
    delete bw;
    delete cw;
    delete ui;
}

void MainWindow::on_actionClear_triggered()
{
    aw->clearRect();
}

void MainWindow::awidget_selected(int lTopX, int lTopY, int rBottomX, int rBottomY)
{
    lTopX *= k;
    lTopY *= k;
    rBottomX *= k;
    rBottomY *= k;

    ImageResizer::redrawImage(*origImage, &(bw->image), lTopX, lTopY, rBottomX, rBottomY);
    bw->repaint();    
    bw->sizeX = rBottomX - lTopX;
    bw->sizeY = rBottomY - lTopY;

    ImageResizer::redrawImage(*origImage, &(cw->image), lTopX, lTopY, rBottomX, rBottomY);
    cw->changedImage = cw->image;
    cw->moving = true;
    cw->repaint();
    cw->sizeX = rBottomX - lTopX > 350 ? 350 : rBottomX - lTopX;
    cw->sizeY = rBottomY - lTopY > 350 ? 350 : rBottomY - lTopY;   
}


void MainWindow::on_actionBW_triggered()
{
    cw->bwFilter();
}

void MainWindow::on_actionNegative_triggered()
{
    cw->negativeFilter();
}

void MainWindow::on_actionOrdered_dither_triggered()
{
    cw->orderedDither(8);
}

void MainWindow::on_actionSave_triggered()
{
    QString url =
            QFileDialog::getSaveFileName(this,
                                        "Save picture", QDir::currentPath(),
                                        tr("JPEG picture (*.jpg);; BMP picture (*.bmp);; "
                                           "PNG picture (*.png) ;; All Files(*)"));
    cw->curImage.save(url);
}

void MainWindow::on_actionOpen_triggered()
{
    QUrl fileUrl =
            QFileDialog::getOpenFileUrl(this,
                                        "Open picture", QUrl("FIT_16209_ Fediaeva_Filter_Data"),
                                        tr("JPEG picture (*.jpg);; BMP picture (*.bmp);; "
                                           "PNG picture (*.png) ;; All Files(*)"));
    if (!fileUrl.isEmpty()){
        FileDriver floader(fileUrl);
        QImage image = floader.loadImage();
        *origImage = image;

        QImage resized;
        ImageResizer resizer(*origImage);

        if (image.height() > 350 || image.width() > 350){
             resized = resizer.resize(350.0, 350.0);
        } else {
            resized = resizer.resize(image.width(), image.height());
        }
        aw->setImage(resized);
        aw->setSizeX(resizer.getNewSizeX());
        aw->setSizeY(resizer.getNewSizeY());
        aw->setRectX1(0);
        aw->setRectX2(resizer.getNewSizeX());
        k = resizer.getK();
        aw->setK(k);
        aw->repaint();
        ui->actionSelect_square->setEnabled(true);
        ui->actionR2Bmp->setEnabled(true);
        ui->actionClear->setEnabled(true);
        ui->actionSelect_square->setChecked(false);
    }
}

void MainWindow::on_actionSelect_square_toggled(bool toggled)
{
    if (toggled){
        aw->selectOn = true;
        double h = origImage->height() / k;
        double w = origImage->width() / k;
        double mk = 175/k;
        aw->centerSquare(round(w/2 - mk),
                         round(w/2 + mk),
                         round(h/2 - mk),
                         round(h/2 + mk));
    } else {
        aw->selectOn = false;
    }
}

void MainWindow::on_actionR2Bmp_triggered()
{
    bw->image = cw->curImage;
    cw->image = bw->image;
    bw->repaint();
}

void MainWindow::on_actionBlur_triggered()
{
    cw->blurFilter();
}

void MainWindow::on_actionRoberts_triggered()
{
    cw->roberts();
}

void MainWindow::on_actionError_diffusion_dither_triggered()
{
    cw->errDifDither();
}

void MainWindow::on_actionWatercoloring_triggered()
{
    cw->watercolor();
}

void MainWindow::on_actionStamping_triggered()
{
    cw->stamping();
}

void MainWindow::on_actionSobel_triggered()
{
    cw->sobel();
}

void MainWindow::on_actionAuthor_triggered()
{
    AboutDialog d;
    d.exec();
}

void MainWindow::on_actionSettings_triggered()
{
    RotationDialog rotationDialog;
    rotationDialog.setSettings(settings);
    rotationDialog.exec();
}

void MainWindow::on_actionDuplication_triggered()
{
    cw->duplicate();
}

void MainWindow::on_actionGamma_correction_triggered()
{
    cw->gamma();
}

void MainWindow::on_actionSharpness_triggered()
{
    cw->sharpnessFilter();
}

void MainWindow::on_actionConstriction_triggered()
{
    cw->constrictionFilter();
}

void MainWindow::on_actionErozy_triggered()
{
    cw->erozyFilter();
}
