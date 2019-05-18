qt-segment
==========

qt-segment is a Qt extension of the image segmentation implementation of
[Efficient Graph-Based Image Segmentation](http://cs.brown.edu/~pff/segment/) by
[Pedro F. Felzenszwalb](http://cs.brown.edu/~pff/) and [Daniel P. Huttenlocher](http://www.cs.cornell.edu/~dph/).

This image segmentation algorithm needs 3 parameters :
* sigma: how much is the image blurred during preprocessing
* K (threshold): constant for treshold function. In very short, allowed amount of color difference for two image components to merge
* min: minimum allowed size of an image component

This algorithm is under GPL (2 or later version) license, and this extension is under MIT license.

## What does this extension improve
* It is cross-platform; Windows, Linux, Mac
* An interface was added in order for the user to apprehend how each parameter affect the segmentation processing (see below)
* The algorithm can now load and save a lot of new image formats
([BMP, GIF, JPG, JPEG, PNG, PBM, PGM, PPM, XBM, XPM](http://qt-project.org/doc/qt-5.0/qtgui/qimage.html#reading-and-writing-image-files)).

This extension has been implemented by [Sébastien Drouyer](http://sebastien.drouyer.com).

## Screenshot of the visual interface
![alt text](https://raw.github.com/sdrdis/qt-segment/master/screenshot.png "Screenshot")
