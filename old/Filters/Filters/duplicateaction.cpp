#include "duplicateaction.h"

DuplicateAction::DuplicateAction()
{

}

void DuplicateAction::run(QImage image, QImage *outImage)
{
    QImage center(175, 175, QImage::Format_ARGB32);
    ImageResizer::redrawImage(image, &center, 87, 87, 262, 262);
    ImageResizer resizer(center);
    *outImage = resizer.resize(350, 350);
}
