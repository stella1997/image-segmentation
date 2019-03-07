//
//  main.cpp
//  image-segmentation
//
//  Created by 孙亚歌 on 2019/1/10.
//  Copyright © 2019 孙亚歌. All rights reserved.
///Users/sunyage/Pictures/pap.er/_nO_HMzu9tU.jpg


#include <cstdlib>
#include <cstdio>
#include <ctime>
#include <stdio.h>

#include "slic.h"
#include "opencv2/opencv.hpp"

#include "opencv2/opencv.hpp"
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/imgproc/imgproc.hpp"
#include <stdio.h>
#include <math.h>
#include <vector>
#include <float.h>
using namespace std;
using namespace cv;

#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <stdio.h>
#include <math.h>
#include <vector>
#include <float.h>
using namespace std;

#include "slic.h"

int main(int argc, char *argv[]) {
    /* Load the image and convert to Lab colour space. */
    IplImage *image = cvLoadImage(argv[1], 1);
    IplImage *lab_image = cvCloneImage(image);
    cvCvtColor(image, lab_image, CV_BGR2Lab);
    
    /* Yield the number of superpixels and weight-factors from the user. */
    int w = image->width, h = image->height;
    int nr_superpixels = atoi(argv[2]);
    int nc = atoi(argv[3]);
    
    double step = sqrt((w * h) / (double) nr_superpixels);
    
    /* Perform the SLIC superpixel algorithm. */
    Slic slic;
    slic.generate_superpixels(lab_image, step, nc);
    slic.create_connectivity(lab_image);
    
    /* Display the contours and show the result. */
    slic.display_contours(image, CV_RGB(255,0,0));
    cvShowImage("result", image);
    cvWaitKey(0);
    cvSaveImage(argv[4], image);
}
