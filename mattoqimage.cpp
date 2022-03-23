#include "mattoqimage.h"

MatToQimage::MatToQimage()
{

}


MatToQimage::~MatToQimage() {

}

QImage MatToQimage::QImageFromMat(Mat frame) {
    // Convert Mat to QImage
    imshow("image", frame);
    QImage result = QImage((const uchar *)frame.data,
        frame.cols,
        frame.rows,
        frame.step,
        QImage::Format_RGB888).rgbSwapped();
    return result;
}
