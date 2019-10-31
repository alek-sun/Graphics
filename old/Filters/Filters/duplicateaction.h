#ifndef DUPLICATEACTION_H
#define DUPLICATEACTION_H

#include "effect.h"
#include "imageresizer.h"

class DuplicateAction : public Effect
{
public:
    DuplicateAction();

    void run(QImage image, QImage *outImage);
};

#endif // DUPLICATEACTION_H
