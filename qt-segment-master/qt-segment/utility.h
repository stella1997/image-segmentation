#ifndef UTILITY_H
#define UTILITY_H

#include <QImage>
#include <image.h>
#include <misc.h>

class Utility
{
public:
    Utility();

    static image <rgb> * qImageToImage(QImage image);
    static QImage imageToQImage(image<rgb> * im);
    static image<rgb> *segmentImage(image<rgb> *im, float sigma, float c, int min_size, int *num_ccs);
};

#endif // UTILITY_H
