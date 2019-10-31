#include "cwidget.h"
#include "blurfilter.h"
#include "duplicateaction.h"
#include "errordiffeffect.h"
#include "imageresizer.h"
#include "negativeeffect.h"
#include "orderdithereffect.h"
#include "robertseffect.h"
#include "sobel.h"
#include "bweffect.h"
#include "rotateaction.h"
#include "gammaeffect.h"
#include "stampfilter.h"
#include "sharpfilter.h"
#include "watercolorfilter.h"
#include "expansionfilter.h"

using std::vector;

CWidget::CWidget(QWidget *parent) : QWidget(parent)
{
    changedImage = QImage(350, 350, QImage::Format_ARGB32);
    changedImage.fill(QColor(255,255,255,255));
    image = QImage(350, 350, QImage::Format_ARGB32);
    image.fill(QColor(255,255,255,255));
    settings = new Settings();
    settings->angle = 0;
    settings->roberts = 5;
    settings->sobel = 5;
    settings->gamma = 1.2;
    settings->changed = false;
}


void CWidget::bwFilter()
{
    BWEffect* bw = new BWEffect();
    delete(curFilter);
    curFilter = bw;
    repaint();
}

void CWidget::negativeFilter()
{
    NegativeEffect* neg = new NegativeEffect();
    delete(curFilter);
    curFilter = neg;
    repaint();
}

void CWidget::orderedDither(int n)
{
    OrderDitherEffect* d = new OrderDitherEffect();
    delete (curFilter);
    curFilter = d;
    repaint();
}


void CWidget::blurFilter()
{
    BlurFilter* f = new BlurFilter();
    delete (curFilter);
    curFilter = f;
    repaint();
}

void CWidget::sharpnessFilter()
{
    SharpFilter* f = new SharpFilter();
    delete (curFilter);
    curFilter = f;
    repaint();
}

void CWidget::roberts()
{
    RobertsEffect* f = new RobertsEffect(settings);
    delete (curFilter);
    curFilter = f;
    repaint();
}

void CWidget::sobel()
{
    Sobel* f = new Sobel(settings);
    delete (curFilter);
    curFilter = f;
    repaint();
}

void CWidget::stamping()
{
    StampFilter* f = new StampFilter();
    delete(curFilter);
    curFilter = f;
    repaint();
}

void CWidget::errDifDither()
{
    ErrorDiffEffect* f = new ErrorDiffEffect();
    delete (curFilter);
    curFilter = f;
    repaint();
}

void CWidget::watercolor()
{
    WatercolorFilter *f = new WatercolorFilter();
    delete (curFilter);
    curFilter = f;
    repaint();
}

void CWidget::duplicate()
{
    DuplicateAction* f = new DuplicateAction();
    delete (curFilter);
    curFilter = f;
    repaint();
}

void CWidget::gamma()
{
    GammaEffect *f = new GammaEffect(settings);
    delete (curFilter);
    curFilter = f;
    repaint();
}

void CWidget::erozyFilter()
{
    ExpansionFilter *f = new ExpansionFilter(0);
    delete (curFilter);
    curFilter = f;
    repaint();
}

void CWidget::constrictionFilter()
{
    ExpansionFilter *f = new ExpansionFilter(12);
    delete (curFilter);
    curFilter = f;
    repaint();
}

void CWidget::rotate()
{
    RotateAction *f = new RotateAction(settings, sizeX, sizeY);
    delete (curFilter);
    curFilter = f;
    repaint();
}


void CWidget::paintEvent(QPaintEvent *event)
{
    if (settings->changed && curFilter != nullptr){
        curFilter->setNeedRedraw(true);
    }
    if (!moving){
        curImage = image;
        if (curFilter != nullptr && curFilter->needRedraw){
            curFilter->run(curImage, &changedImage);
            curFilter->needRedraw = false;
        } else {
            changedImage = image;
        }
        if (settings->angle != 0){
            RotateAction f(settings, sizeX, sizeY);
            f.run(changedImage, &changedImage);
        }
    } else {
        settings->angle = 0;
        if (curFilter != nullptr){
            delete (curFilter);
            curFilter = nullptr;
        }
    }

    QPainter painter(this);
    painter.drawImage(0, 0, changedImage);      
    curImage = changedImage;
    bits = changedImage.bits();
    moving = false;
}

