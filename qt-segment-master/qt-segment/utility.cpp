#include "utility.h"
#include "segment-image.h"

Utility::Utility()
{
}

image <rgb> * Utility::qImageToImage(QImage im) {
    image<rgb> *input = new image<rgb>(im.width(), im.height(), true);

    for (int x = 0; x < im.width(); x++) {
        for (int y = 0; y < im.height(); y++) {
            rgb pix;
            QRgb pixF = im.pixel(x, y);
            pix.r = qRed(pixF);
            pix.g = qGreen(pixF);
            pix.b = qBlue(pixF);
            input->data[y * im.width() + x] = pix;
        }
    }

    return input;
}

QImage Utility::imageToQImage(image<rgb> * im) {
    QImage res(im->width(), im->height(), QImage::Format_RGB32);

    for (int x = 0; x < im->width(); x++) {
        for (int y = 0; y < im->height(); y++) {
            rgb pix = im->data[y * im->width() + x];
            res.setPixel(x, y, qRgb(pix.r, pix.g, pix.b));
        }
    }

    return res;
}

image<rgb> *Utility::segmentImage(image<rgb> *im, float sigma, float c, int min_size, int *num_ccs) {
    return segment_image(im, sigma, c, min_size, num_ccs);
}
