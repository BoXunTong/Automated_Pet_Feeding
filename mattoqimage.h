#ifndef MATTOQIMAGE_H
#define MATTOQIMAGE_H

#include<opencv2/opencv.hpp>
//qt & C++ includes
#include <QImage>
#include <vector>

using namespace cv;

class MatToQimage
{
public:
    MatToQimage();
    ~MatToQimage();

public slots:
    QImage QImageFromMat(Mat frame);
};

#endif // MATTOQIMAGE_H
