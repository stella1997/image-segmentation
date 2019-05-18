#include <cstdio>
#include <cstdlib>
#include <image.h>
#include <misc.h>

#include <QApplication>
#include <QImage>
#include "utility.h"
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    if (argc > 1) {
        if (argc != 6) {
            fprintf(stderr, "usage: %s sigma k min input output\n", argv[0]);
            return 1;
        }

        float sigma = atof(argv[1]);
        float k = atof(argv[2]);
        int min_size = atoi(argv[3]);

        printf("loading input image.\n");
        image<rgb> *input = Utility::qImageToImage(QImage(argv[4]));

        printf("processing\n");
        int num_ccs;
        image<rgb> *seg = Utility::segmentImage(input, sigma, k, min_size, &num_ccs);
        Utility::imageToQImage(seg).save(argv[5]);

        printf("got %d components\n", num_ccs);
        printf("done! uff...thats hard work.\n");

        return 0;

    } else {
        MainWindow w;
        w.setWindowState(Qt::WindowMaximized);
        w.show();

        return a.exec();
    }
}


